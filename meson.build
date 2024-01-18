project('todo', 'c')
inc_dir = include_directories('include')
sources = files(
  'src/main.c'     ,
  'src/todo.c'     ,
  'src/commands.c' ,
  'src/config.c'   ,
  'src/handler.c'  ,
  'src/help.c'     ,
)
executable('todo', sources, include_directories: inc_dir)
