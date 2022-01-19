# Sudoku - dalam C dan OpenGL
### Implementasi simple dari Sudoku dalam C dan OpenGL
---
**Sementara masih mendukung Windows, build Unix memiliki bug pada saat penataan angka**

**PERHATIAN: Algoritma penataan angka masih belum sempurna, angka masih sangat berpola dan terlalu mudah untuk diselesaikan begitu sudah banyak angka yang terlihat**
---
## Download
Silahkan masuk ke **[Halaman Release](https://github.com/EmiyaSyahriel/sudoku/releases)**

## Pustaka Apl yang dipakai:
- GLFW 3.3
- GLEW

## Cara build:
### Yang diperlukan:
- CMake
- Config GLEW & GLFW untuk CMake

### Windows (Visual Studio)
**Pastikan memiliki Visual Studio yang sudah terintegrasi dengan CMake (CMake Integration for Visual Studio).**

Buka folder dimana CMakeLists.txt berada di Visual Studio, pilih konfigurasi `x64-FullRelease`, 
Lalu pilih `Build > Build All`. 

dengan cara ini, VS akan membuild versi Bahasa Indonesia (sudoku.exe) dan English (sudoku_en.exe) di folder `out\build\x64-FullRelease`

### Linux
**Pastikan sudah memasang paket `cmake make build-essential libglfw3-dev libglew-dev` lewat manajer paket masing-masing distro.**

- Buka terminal, sebaiknya di direktori khusus agar lebih rapi.
- Di terminal, ketik :
```
git clone https://github.com/EmiyaSyahriel/sudoku.git
cd sudoku
mkdir build & cd build
cmake ..
make
```
- Berkas binari akan tersedia di direktori `build` jika build berhasil
  - sudoku (Bahasa Indonesia)
  - sudoku_en (English)

## Lisensi
### CC0 1.0

Karya ini sudah diserahkan kepada domain publik, sehingga karya ini bebas diubah, disebarluaskan, dan dipakai dalam produk komersial tanpa harus menyebutkan pihak kami ([EmiyaSyahriel](https://github.com/EmiyaSyahriel)).