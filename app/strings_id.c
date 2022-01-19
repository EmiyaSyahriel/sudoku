#ifdef GAME_LANGUAGE_ID
#include "strings.h"

/**
* 
* Symbols is actually a normal ASCII character, it's just textured that way
* Left Arrow   : '{'
* Right Arrow  : '}'
* Up Arrow     : '^'
* Down Arrow   : '~'
* Enter Symbol : '`'
* 
*/

const char* windowName = "C Sudoku";
const char* authorName = "EmiyaSyahriel";
const char* errGLFWInit = "Gagal memuat GLFW, diperlukan untuk membuat konteks OpenGL";
const char* errGLEWInit = "Gagal memuat GLEW, diperlukan untuk memuat inti OpenGL";
const char* glStartupLog = "OpenGL versi %s, memakai perangkat : %s";
const char* logArgval = "Argval argument is given...";
const char* errTitle = "Galat";
const char* str_OK = "OK";
const char* str_Yes = "Ya";
const char* str_No = "Tidak";
const char* str_Circle = "O";
const char* str_Cross = "X";
const char* arg_run = "--run";
const char* arg_OK = "__ok";
const char* glErrorFormat = "Galat OpenGL 0x%08x pada %s:%i";
const char* glShaderError = "Galat dalam Pembayang OpenGL : %s";
const char* glShaderCompiled = "Pembayang OpenGL berhasil dimuat.";

const char* glShpArg[5] = { "v_vpos","v_uv","v_sel","color_a","color_b" };
const char* textureLoadFinish = "Tekstur berhasil dimuat";
const char* bufferGenFinish = "Sanggan OpenGL berhasil dimuat";
const char* gmFPS = "%i FPS";

const char* splExit = "[Esc] Keluar";
const char* splEnter = "[`] Skip";
const char* splashName = "Sudoku - dalam C dan OpenGL";
const char* splRdmText[10] = {
	"8 bit? ini cuma 1 malah :)",
	"Lebih buriq dari Api Gratis!",
	"Bahasa C beneran susah pak :')",
	"OpenGL itu 3D! bukan cmD!",
	"Pake OpenGL btw, bukan cmd",

	"Apakah Watatsumi = Danau Toba?",
	"github.com/EmiyaSyahriel/sudoku",
	"Kode sumber bebas diakses!",
	"Kode sumber bebas diubah!",
	"Bisakah game jadi NFT?"
};

const char* scnNameSplash = "Ini judul btw...";
const char* scnNameMenu  = "C Sudoku";
const char* scnNameBoard = "Papan Angka";
const char* scnNameEnd   = "Permainan Selesai";

const char* menuOptionSliderFormat = "{ %2i }";
const char* menuOptionSliderStrFormat = "{ %s }";
const char* menuOptionHiddenCount = "Angka yg ditutup";
const char* menuOptionShowHint = "Kasih petunjuk";
const char* menuOptionShowFPS  = "Tampilkan FPS";
const char* menuOptionShowTime = "Tampilkan Waktu";
const char* menuOptionPlay = "Mainkan";
const char* menuOptionPlayDesc = "Siapkan otakmu! }";
const char* menuDisplayLegend1 = "[^] [~] Ganti Pilihan";
const char* menuDisplayLegend2 = "[{] [}] Ganti Nilai";
const char* menuDisplayLegend3 = "  [`]   Pilih";
const char* menuDisplayLegend4  = " [Esc]  Keluar";
const char* menuWarningError[4] = {
   //12345678901234567890123456789012
	"INFO: ",
	"Algoritma penata angka masih",
	"belum sempurna, angka masih",
	"sangat berpola & mudah ditebak"
};

const char* boardBackgroundCross = "+---+---+---+";
const char* boardBackgroundTiles = "|   |   |   |";
const char* boardGenerating1 = "Bentar! masih menata angka";
const char* boardGenerating2 = "pada papan permainan...";
const char* boardErrorVertical =   "Coba lihat keatas/kebawah deh";
const char* boardErrorHorizontal = "Coba lihat ke samping deh";
const char* boardErrorBlock =      "Coba lihat ke sekitar deh";
const char* boardDisplayLegend1 =  "[1-9]  Masukkan Angka";
const char* boardDisplayLegend2 =  " [0]   Kosongkan";
const char* boardDisplayLegend3 =  "[{}^~] Pindahan Kursor";
const char* boardDisplayLegend4 =  "[C] Cek Semua | [`] Cek Satu";
const char* boardDisplayLegend5 =  "[Esc] Jeda Permainan";
const char* boardTimeFormat = "%02i:%02i:%02i";
const char* boardPaused = "Permainan di Jeda";
const char* boardPausedLegend1 = "[Esc] Keluar";
const char* boardPausedLegend2 = "[`] Lanjutkan";

const char* endScreenLevelName   = "Angka Ditutup";
const char* endScreenLevelFormat = "%i";
const char* endScreenTimeName = "Selesai Dalam";
const char* endScreenTimeFormat = "%02i:%02i:%02i";
const char* endScreenLegend1 = "[`] Kembali ke menu";
#endif