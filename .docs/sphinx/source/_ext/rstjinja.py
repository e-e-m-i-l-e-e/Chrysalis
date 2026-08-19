import os
from jinja2 import Template

def rstjinja(app, docname, source):
    template = Template(source[0])
    context = {
        "hostname": app.config.hostname,
        'documentation_dir': app.config.documentation_dir,
        'documentation_dir_relative': app.config.documentation_dir_relative,
        'modules': app.config.modules,
    }
    source[0] = template.render(context)

def setup(app):
    app.add_config_value("hostname", "", "env")
    app.add_config_value('documentation_dir', os.path.abspath('.'), 'env')
    app.add_config_value('documentation_dir_relative', os.path.abspath('.'), 'env')
    app.add_config_value("modules", [], "env")
    app.connect('source-read', rstjinja)