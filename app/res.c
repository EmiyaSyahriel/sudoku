#include "sudoku.h"

char* texture = 
"........""........""........""........" ".....#..""........""...##...""........" "........""........""........""...#...." "........""........""........""........"
"........""....#...""...#.#..""..#..#.." "..#####."".##...#.""..#..#..""...#...." "....#...""...#....""...#....""...#...." "........""........""........""......#."
"........""....#...""...#.#.."".######." ".#..#..""..##..#..""...##...""...#...." "...#....""....#..."".#.#.#..""...#...." "........""........""........"".....#.."
"........""....#...""........""..#..#.." "..####..""....#...""..#.#...""........" "...#....""....#...""..###...""########" "........""########""........""....#..."
"........""....#...""........"".######." "...#..#.""...#...."".#...#.#""........" "...#....""....#..."".#.#.#..""...#...." "........""........""........""...#...."
"........""........""........""..#..#.." ".#####..""..#..##."".#....#.""........" "...#....""....#...""...#....""...#...." "...##...""........""...##...""..#....."
"........""....#...""........""........" "..#....."".#...##.""..####.#""........" "....#...""...#....""........""...#...." "....#...""........""...##..."".#......"
"........""........""........""........" "........""........""........""........" "........""........""........""...#...." "...#....""........""........""........"

"........""........""........""........" "........""........""........""........" "........""........""........""........" "........""........""........""..####.."
"..####..""....#...""..####..""..####.." ".....##."".######.""..#####."".######." "..####..""..####..""........""........" ".....##.""........"".##....."".#....#."
".##...#.""...##..."".#....#."".#....#." "....#.#."".#......"".#......""......#." ".#....#."".#....#.""...##...""...##..." "...##...""........""...##...""......#."
".#.#..#.""....#..."".....#..""....##.." "...#..#."".#####.."".#####.."".....#.." "..####..""..#####.""...##...""...##..." ".##....."".######."".....##.""......#."
".#..#.#.""....#...""...##...""......#." "..#...#.""......#."".#....#.""....#..." ".#....#.""......#.""........""........" "...##...""........""...##...""...###.."
".#...##.""....#...""..#....."".#....#." ".######."".#....#."".#....#.""...#...." ".#....#."".#....#.""...##...""...##..." ".....##."".######."".##.....""........"
"..####..""..#####."".######.""..####.." "......#.""..####..""..####..""...#...." "..####..""..####..""...##...""....#..." "........""........""........""...##..."
"........""........""........""........" "........""........""........""........" "........""........""........""........" "........""........""........""........"

"........""........""........""........" "........""........""........""........" "........""........""........""........" "........""........""........""........"
"..####..""..####.."".#####..""..####.." ".#####.."".######."".######.""..#####." ".#....#.""...###..""....###."".#...##." ".#......"".#....#."".#....#.""..####.."
".#....#."".#....#."".#....#."".#....#." ".#....#."".#......"".#......"".#......" ".#....#.""....#...""......#."".#.##..." ".#......"".##..##."".##...#."".#....#."
".#.#..#."".#....#."".#####.."".#......" ".#....#."".####..."".####..."".#.####." ".######.""....#...""......#."".##....." ".#......"".#.##.#."".#.#..#."".#....#."
".#.####."".#....#."".#....#."".#......" ".#....#."".#......"".#......"".#....#." ".#....#.""....#...""......#."".##....." ".#......"".#.##.#."".#..#.#."".#....#."
".#......"".######."".#....#."".#....#." ".#....#."".#......"".#......"".#....#." ".#....#.""....#...""..#...#."".#.##..." ".#......"".#....#."".#...##."".#....#."
"..#####."".#....#."".#####..""..####.." ".#####.."".######."".#......""..#####." ".#....#.""...###..""...###.."".#...##." ".######."".#....#."".#....#.""..####.."
"........""........""........""........" "........""........""........""........" "........""........""........""........" "........""........""........""........"

"........""........""........""........" "........""........""........""........" "........""........""........""........" "........""........""........""........"
".#####..""..####.."".#####..""..#####." ".######."".#....#."".#...#..""..#...#." ".#....#.""..#...#."".######.""...##..." ".#......""...##...""....#...""........"
".#....#."".#....#."".#....#."".#......" "...#...."".#....#.""..#..#..""..#...#." "..#..#..""...#.#.."".....#..""...#...." "..#.....""....#...""...###..""........"
".#####.."".#....#."".#####..""..####.." "...#...."".#....#.""..#..#..""..#.#.#." "...##...""....#...""....#...""...#...." "...#....""....#...""..#.#.#.""........"
".#......"".#..#.#."".#..#...""......#." "...#...."".#....#.""...#.#..""..#.#.#." "...##...""....#...""...#....""...#...." "....#...""....#...""....#...""........"
".#......"".#...##."".#...#..""......#." "...#...."".#....#.""...#.#..""...#.#.." "..#..#..""....#...""..#.....""...#...." ".....#..""....#...""....#...""........"
".#......""..#####."".#....#."".#####.." "...#....""..####..""....##..""...#.#.." ".#....#.""....#..."".######.""...##..." "......#.""...##...""....#..."".######."
"........""........""........""........" "........""........""........""........" "........""........""........""........" "........""........""........""........"

"........""........""........""........" "........""........""........""........" "........""........""........""........""........" "........""........""........"
"......#.""........"".#......""........" "......#.""........""........""........" ".#......""....#...""......#."".#......""...#...." "........""........""........"
"...#..#.""..####.."".#......""........" "......#.""..####..""..###...""...####." ".#......""........""........"".#..#...""...#...." ".##.##.."".####..."".####..."
"..#...#.""......#."".#####..""..#####." "..#####."".#....#."".#......""..#...#." ".#####..""...##..."".....##."".#.#....""...#...." ".#.#..#."".#...#.."".#...#.."
".######.""..#####."".#....#."".#......" ".#....#."".######."".#......""..#...#." ".#....#.""....#...""......#."".##.....""...#...." ".#.#..#."".#...#.."".#...#.."
"..#....."".#....#."".#....#."".#......" ".#....#."".#......"".###....""...####." ".#....#.""....#...""......#."".#.#....""...#...." ".#....#."".#...#.."".#...#.."
"...#....""..#####."".#####..""..#####." "..#####.""..#####."".#......"".#....#." ".#....#.""..####..""..#...#."".#..#...""....#..." ".#....#."".#...#..""..####.."
"........""........""........""........" "........""........"".#......""..####.." "........""........""...###..""........""........" "........""........""........"

"........""........""........""........""........" "........""........""........""........" "........""........""........""...#...." "........""........""........"
"........""........""........""........"".#......" "........""........""........""........" "........""........""...#....""...#...." "....#...""....#..."".######."
".#####..""..#####."".####...""..####.."".#......" ".#...#.."".#...#.."".#....#."".##.##.." "..#...#.""..####..""..#.....""...#...." ".....#..""....#..."".##..##."
".#....#."".#....#."".#...#.."".#......"".#......" ".#...#.."".#...#.."".#....#.""..###..." "..#...#."".....#.."".######.""...#...." ".######.""....#..."".#.##.#."
".#....#."".#....#."".#......"".#####.."".###...." ".#...#..""..#.#..."".#..#.#.""...#...." "..#...#.""...##...""..#.....""...#...." ".....#..""..#.#.#."".#.##.#."
".#####..""..#####."".#......"".....#.."".#......" ".#...#..""..#.#..."".#..#.#.""..###..." "...####.""...#....""...#....""...#...." "....#...""...###.."".##..##."
".#......""......#."".#......"".####...""..###..." "..####..""...#....""..##.##."".##.##.." "......#.""..####..""........""...#...." "........""....#..."".######."
".#......""......#.""........""........""........" "........""........""........""........" "..####..""........""........""...#...." "........""........""........"
;


char* shader_v = "\n\
attribute vec2 v_vpos, v_uv;\n\
attribute float v_sel;\n\
varying vec2 f_uv;\n\
varying float f_sel;\n\
\n\
void main(){\n\
	gl_Position = vec4(v_vpos, 0.0, 1.0);\n\
	f_uv = v_uv;\n\
	f_sel = v_sel;\n\
}\n\
";








char* shader_f = "\n\
uniform sampler2D f_tex;\n\
varying vec2 f_uv;\n\
varying float f_sel;\n\
uniform vec4 color_a, color_b;\n\
const float up_bound = 0.1372;\n\
const float bt_bound = 0.1803;\n\
\n\
float lerpfc(float v,float a,float b) { return (v - a) / (b - a); }\n\
void main(){\n\
	float t = texture2D(f_tex, f_uv).r;\n\
	t = lerpfc(t, bt_bound, up_bound);\n\
	t = mix(t, 1.0 - t, f_sel);\n\
	gl_FragColor = mix(color_a, color_b, t);\n\
}\n\
";