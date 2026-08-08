project = 'Chrysalis'
copyright = '2026, emilyyy0621@gmail.com'
author = 'emilyyy0621@gmail.com'
release = '1.0'

extensions = [
    "breathe"
]

breathe_projects = {
    "Chrysalis": "../../.build"
}

breathe_default_project = "Chrysalis"

templates_path = ['_templates']
exclude_patterns = []

html_theme = 'sphinxawesome_theme'
html_title = 'Chrysalis'
html_permalinks = False
html_static_path = ['_static']
html_css_files = ['custom.css']
html_sidebars = {
    'index': [],
    'search': [],
    'app/index': [],
    'app/chrysalis*': ['sidebar_section_nav.html'],
    'app/clo3d*': ['sidebar_section_nav.html'],
    'app/clo3d/**': ['sidebar_section_nav.html'],
    'app/valentina*': ['sidebar_section_nav.html'],
    'module/index': [],
    'module/pattern*': ['sidebar_section_nav.html'],
    'module/renderer*': ['sidebar_section_nav.html'],
    'module/hooks*': ['sidebar_section_nav.html'],
    'development/**': ['sidebar_section_nav.html'],
}

html_theme_options = {
    "main_nav_links": {
        "Applications": "/app/",
        "Modules": "/module/",
    },
}