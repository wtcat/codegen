static_library(google)

target_sources(google
	PRIVATE
	protobuf/io/coded_stream.cc
	protobuf/io/io_win32.cc
	protobuf/io/printer.cc
	protobuf/io/strtod.cc
	protobuf/io/tokenizer.cc
	protobuf/io/zero_copy_stream.cc
	protobuf/io/zero_copy_stream_impl.cc
	protobuf/io/zero_copy_stream_impl_lite.cc

	protobuf/stubs/bytestream.cc
	protobuf/stubs/common.cc
	protobuf/stubs/int128.cc
	protobuf/stubs/status.cc
	protobuf/stubs/statusor.cc
	protobuf/stubs/stringpiece.cc
	protobuf/stubs/stringprintf.cc
	protobuf/stubs/structurally_valid.cc
	protobuf/stubs/strutil.cc
	protobuf/stubs/substitute.cc
	protobuf/stubs/time.cc
)
