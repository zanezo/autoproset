AC_INIT([my_project], [1.0], [youremail@example.com])
AM_INIT_AUTOMAKE([foreign])  # foreign: 不强制遵循 GNU 项目结构
AC_CONFIG_SRCDIR([src/main.c])  # 检查 src/main.c 是否存在
AC_CONFIG_HEADERS([config.h])   # 自动生成 config.h 头文件

# 检查编译器
AC_PROG_CC

# 检查 pkg-config 和 GTK+ 依赖（可选）
PKG_CHECK_MODULES([GTK], [gtk4])

# 生成 Makefile
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

PKG_CHECK_MODULES([GTK4], [gtk4])
AC_SUBST([GTK4_CFLAGS])
AC_SUBST([GTK4_LIBS])
