bin_PROGRAMS = autoProset      # 要生成的可执行文件名
autoProset_SOURCES = main.c func/func.c    # 项目源代码文件
autoProsetdir = E:/autoProset/dev/bin

autoProset_CFLAGS = $(GTK_CFLAGS)  # 使用 pkg-config 提供的 CFLAGS
autoProset_LDADD = $(GTK_LIBS)    # 链接 GTK+ 的库
autoProset_LDFLAGS = -mwindows -static-libgcc -static-libstdc++ -LE:/MSYS2/setuped/ucrt64/lib -lgtk-4 
autoProset_CPPFLAGS = -IE:/MSYS2/setuped/ucrt64/include
