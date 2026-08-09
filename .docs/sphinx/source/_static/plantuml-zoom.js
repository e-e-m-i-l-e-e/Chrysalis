// Wraps every PlantUML diagram (sphinxcontrib.plantuml renders each as
// <p class="plantuml"><object type="image/svg+xml" style="width:...px;
// height:...px;">...</object></p>) in a scrollable, zoomable viewport.
//
// Runs automatically for any diagram on the page - no per-diagram markup
// needed. Zoom is implemented by resizing the <object>/<img> element's
// actual width/height (not CSS transform), so the scrollable viewport's
// scrollbars correctly track the zoomed size.
(function () {
  'use strict';

  var MIN_ZOOM = 0.25;
  var MAX_ZOOM = 3;
  var ZOOM_STEP = 0.25;

  function parsePxStyle(styleValue, prop) {
    if (!styleValue) return null;
    var match = new RegExp(prop + '\\s*:\\s*([\\d.]+)px', 'i').exec(styleValue);
    return match ? parseFloat(match[1]) : null;
  }

  function enhance(diagram) {
    var media = diagram.querySelector('object, img');
    if (!media) return;

    var styleAttr = media.getAttribute('style') || '';
    var baseWidth = parsePxStyle(styleAttr, 'width');
    var baseHeight = parsePxStyle(styleAttr, 'height');

    // Fall back to the element's rendered size if no explicit px size
    // was set (e.g. plantuml_output_format left it to the SVG itself).
    if (!baseWidth || !baseHeight) {
      var rect = media.getBoundingClientRect();
      baseWidth = baseWidth || rect.width;
      baseHeight = baseHeight || rect.height;
    }
    if (!baseWidth || !baseHeight) return;

    // Build the new structure, preserving the original element (and its
    // "plantuml" class, so existing background/fill CSS rules still match).
    diagram.classList.add('chrysalis-diagram');

    var toolbar = document.createElement('div');
    toolbar.className = 'chrysalis-diagram-toolbar';
    toolbar.innerHTML =
      '<button type="button" data-action="zoom-out" aria-label="Zoom out">\u2212</button>' +
      '<span class="chrysalis-diagram-zoom-level">100%</span>' +
      '<button type="button" data-action="zoom-in" aria-label="Zoom in">+</button>' +
      '<button type="button" data-action="zoom-reset" class="chrysalis-diagram-reset" aria-label="Reset zoom">Reset</button>';

    var viewport = document.createElement('div');
    viewport.className = 'chrysalis-diagram-viewport';

    diagram.insertBefore(toolbar, media);
    viewport.appendChild(media);
    diagram.insertBefore(viewport, toolbar.nextSibling);

    var zoomLevelLabel = toolbar.querySelector('.chrysalis-diagram-zoom-level');
    var zoom = 1;

    function applyZoom() {
      media.style.width = Math.round(baseWidth * zoom) + 'px';
      media.style.height = Math.round(baseHeight * zoom) + 'px';
      zoomLevelLabel.textContent = Math.round(zoom * 100) + '%';
    }

    function setZoom(next) {
      zoom = Math.min(MAX_ZOOM, Math.max(MIN_ZOOM, next));
      applyZoom();
    }

    toolbar.addEventListener('click', function (event) {
      var button = event.target.closest('button[data-action]');
      if (!button) return;
      if (button.dataset.action === 'zoom-in') setZoom(zoom + ZOOM_STEP);
      else if (button.dataset.action === 'zoom-out') setZoom(zoom - ZOOM_STEP);
      else if (button.dataset.action === 'zoom-reset') setZoom(1);
    });

    // Optional: Ctrl/Cmd + scroll wheel to zoom, same convention as
    // maps/image viewers, without hijacking normal page scrolling.
    viewport.addEventListener(
      'wheel',
      function (event) {
        if (!(event.ctrlKey || event.metaKey)) return;
        event.preventDefault();
        setZoom(zoom + (event.deltaY < 0 ? ZOOM_STEP : -ZOOM_STEP));
      },
      { passive: false }
    );

    applyZoom();
  }

  document.addEventListener('DOMContentLoaded', function () {
    document.querySelectorAll('.plantuml').forEach(enhance);
  });
})();
