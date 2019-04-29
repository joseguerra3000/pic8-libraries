/* 
 * File:   font5x7.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 3 de enero de 2019, 12:44
 */

#ifndef _FONT5X7_MEDLEY_H
#define	_FONT5X7_MEDLEY_H


#ifdef	__cplusplus
extern "C" {
#endif

/**

++#++
#####
++#++
+###+
#####
++#++
++#++


*/

#define FONT5x7_DIODE               (font5x7_medley)
#define FONT5x7_CAPACITOR           (font5x7_medley+5)
#define FONT5x7_FACE_SMILE          (font5x7_medley+10)
#define FONT5x7_FACE_SAD            (font5x7_medley+15)
#define FONT5x7_ARROW_RIGHT_FILLED  (font5x7_medley+20)
#define FONT5x7_ARROW_LEFT_FILLED   (font5x7_medley+25)
#define FONT5x7_ARROW_RIGHT         (font5x7_medley+30)
#define FONT5x7_ARROW_LEFT          (font5x7_medley+25)
    
// personalised simbols 5x7 font
static const unsigned char font5x7_medley[] = {
    0x12, 0x1A, 0xFF, 0x1A, 0x12, // Diode
    0x14, 0x14, 0x77, 0x14, 0x14, // Capacitor
    0x16, 0x26, 0x20, 0x26, 0x16, // Smile Face
    0x26, 0x16, 0x10, 0x16, 0x26, // Sad Face
    0x08, 0x08, 0x3E, 0x1C, 0x08, // right arrow filled
    0x08, 0x1C, 0x3E, 0x08, 0x08, // left arrow filled
    0x08, 0x08, 0x2A, 0x1C, 0x08, // right arrow
    0x08, 0x1C, 0x2A, 0x08, 0x08, // left arrow

};



#ifdef	__cplusplus
}
#endif

#endif	/* FONT5X7_H */

