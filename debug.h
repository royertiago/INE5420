/* debug.h
 * Macros para debug.
 */
#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>

#define print3dM( m ) std::printf( "/% lf % lf % lf % lf\\" #m "\n"\
                                   "|% lf % lf % lf % lf|\n"\
                                   "|% lf % lf % lf % lf|\n"\
                                  "\\% lf % lf % lf % lf/\n",\
                                    m[0][0], m[0][1], m[0][2], m[0][3], \
                                    m[1][0], m[1][1], m[1][2], m[1][3], \
                                    m[2][0], m[2][1], m[2][2], m[2][3], \
                                    m[3][0], m[3][1], m[3][2], m[3][3] )
#define print3dP( v ) std::printf( #v " = (%.3lf %.3lf %.3lf %.3lf)\n", \
                                    v[0][0], v[1][0], v[2][0], v[3][0] )
#define print3dV( v ) std::printf( #v " = (%.3lf %.3lf %.3lf)\n", \
                                    v[0][0], v[1][0], v[2][0] )

#endif // DEBUG_H
