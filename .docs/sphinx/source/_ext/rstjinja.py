import os
from jinja2 import Template

def rstjinja(app, docname, source):
    template = Template(source[0])
    context = {
        'documentation_root': app.config.documentation_root,
    }
    source[0] = template.render(context)

def setup(app):
    app.add_config_value('documentation_root', os.path.abspath('.'), 'env')
    app.connect('source-read', rstjinja)