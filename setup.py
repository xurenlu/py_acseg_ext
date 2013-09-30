#-*- coding:UTF-8 -*-

from distutils.core import setup, Extension

m_acseg = Extension(
	'acseg',
	include_dirs = ["src"],
	sources = [
		'src/acseg_util.c',
		'acseg.c', 'src/acseg_rbtree.c', 'src/acseg_tree.c', 'src/mem_collector.c',
	]
)

setup(
	name = "acseg",
	version = '0.1',
	author = "Chinaren Wei",
	author_email = "weizhonghua.ati@gmail.com",
	url = "https://pysoft.googlecode.com/svn/trunk/c-project/acseg",
	description = "ac segment extension",
	license = "GPL",
	ext_modules = [m_acseg],
)
