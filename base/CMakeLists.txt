#Base library
static_library(base)

target_sources(base
	PRIVATE
	container/observer.c
	resource_base.c
	initializer.cc
)


