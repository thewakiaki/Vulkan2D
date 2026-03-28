# Vulkan2D
Basic Vulkan 2D Framework

-------------------------------------------------------------------------------------

Vulkan API target: 1.4 / Vulkan API ターゲットバージョン: 1.4

-------------------------------------------------------------------------------------
Dependencies / 依存関係

- Vulkan SDK / Vulkan SDK  
- CMake 3.16+ / CMake 3.16以上
- GLFW 3.4+ / GLFW 3.4以上
- GLM / GLM
- SDL3 / SDL3
- fmtlib / fmtlib

-------------------------------------------------------------------------------------
Build Instructions / ビルド手順

To create the builds　first go go to the project root via the terminal and use the following cmake commands for release and debug builds<br><br>
ビルドを作りたい時は、ターミナルでプロジェクトのディレクトリまで移動し, 下記のCMAKEのコマンドを使用してください

  - Debug/デバッグ用 ： cmake -DCMAKE_BUILD_TYPE=Debug -B build-debug 
  - Release/リリース用 ： cmake -DCMAKE_BUILD_TYPE=Release -B build-release

You can replace build-debug and build-relase with a directory name you want to keep the builds in
the command will automatically create the directory and set the directory ready to build the application<br><br>
ビルド先を指定したい場合は、build-debugやbuild-releaseを好きなディレクトリ名に変更してください
ビルド先のディレクトリは自動で作られるため事前に作る必要はありません

After using the debug/release commands use the following the commands to build the app<br><br>
上記のコマンドをターミナルで入力したあとは下記のコマンドでアプリをビルドしてください

  - cmake --build build-debug
  - cmake --build build-release

Again replace build-debug and build-release with the directory you want to build the app<br><br>
自分でターゲットディレクトリを指定した場合、build-debugやbuild-releaseを指定したターゲットディレクトリ名に変更してくたさい


--------------------------------------------------------------------------------------
