all: clean generate-ast cmake

clean:
	rm -rf build
	mkdir build

generate-ast: tools/generate-ast.cc
	pushd tools/ >> /dev/null && \
	g++ -std=c++17 -o ../build/generate-ast generate-ast.cc && \
	popd >> /dev/null

	pushd build/ >> /dev/null && \
	./generate-ast ../ && \
	popd >> /dev/null

cmake:
	pushd build/ && \
	cmake .. && \
	cmake --build . && \
	popd
