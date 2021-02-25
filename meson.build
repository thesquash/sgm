project('sgm', 'c',
  version : '0.90.0',
  default_options : ['warning_level=3'],
  license: 'LGPLv2.1+')


gtk_dep = dependency('gtk+-3.0', version: '>= 3.8.0')

modules_subdir = 'gtk-3.0/modules'
modules_install_dir = join_paths(gtk_dep.get_variable(
  pkgconfig: 'libdir',
  internal: 'libdir',
  default_value: get_option('libdir')), modules_subdir)



shared_module('sgm-flexible-mnemonics',
  sources: [
    'sgm-flexible-mnemonics.c',
  ],
  dependencies: [ gtk_dep ],
  install_dir: modules_install_dir,
  install: true,
)
