#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char* argv[]) {
	const char* fn = "hello.lua";
	// Lua の言語エンジンを初期化
	lua_State* lua = luaL_newstate();

	// Lua のライブラリを使えるようにする
	luaL_openlibs(lua);

	// Lua のスクリプトを読み込む
	printf("%d\n", luaL_dofile(lua, fn));

	return 0;
}