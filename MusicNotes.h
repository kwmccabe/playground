/* see https://en.wikipedia.org/wiki/List_of_musical_symbols */

struct MusicTime {
  String name;  // display name
  float time;   // tone duration = 60000/bpm * time;
};

struct MusicTone {
  String name;  // display name
  int freq;     // tone frequency
  int level;    // display level (keyboard position)
  String type;  // adorn options
};


/* time indexes */
#define t18     0
#define t14     1
#define t13     2
#define t12     3
#define t23     4
#define t34     5
#define T10     6
#define T15     7
#define T20     8
#define T25     9
#define T30     10
#define T35     11
#define T40     12

/* (ascending) time values : { name, time }*/
static MusicTime TIMES[] = {
{ "1/8",  0.125 },  // t18 - (1/8) Thirty-second
{ "1/4",  0.25  },  // t14 - (1/4) Sixteenth
{ "1/3",  0.334 },  // t13 - (1/3) Twelfth
{ "1/2",  0.5   },  // t12 - (1/2) Eighth
{ "2/3",  0.667 },  // t23 - (2/3) Sixth
{ "3/4",  0.75  },  // t34 - (3/4)
{ "1.0",  1.0   },  // T10 - (1/1) Quarter
{ "1.5",  1.5   },  // T15 - (3/2)
{ "2.0",  2.0   },  // T20 - (2/1) Half
{ "2.5",  2.5   },  // T25 - (5/2)
{ "3.0",  3.0   },  // T30 - (3/1) Three-quarter
{ "3.5",  3.5   },  // T35 - (7/2)
{ "4.0",  4.0   },  // T40 - (4/1) Whole note
};

/* tone indexes */
#define fB8     0
#define fBF8    1
#define fAS8    2
#define fA8     3
#define fAF8    4
#define fGS8    5
#define fG8     6
#define fGF8    7
#define fFS8    8
#define fF8     9
#define fE8     10
#define fEF8    11
#define fDS8    12
#define fD8     13
#define fDF8    14
#define fCS8    15
#define fC8     16

#define fB7     17
#define fBF7    18
#define fAS7    19
#define fA7     20
#define fAF7    21
#define fGS7    22
#define fG7     23
#define fGF7    24
#define fFS7    25
#define fF7     26
#define fE7     27
#define fEF7    28
#define fDS7    29
#define fD7     30
#define fDF7    31
#define fCS7    32
#define fC7     33

#define fB6     34
#define fBF6    35
#define fAS6    36
#define fA6     37
#define fAF6    38
#define fGS6    39
#define fG6     40
#define fGF6    41
#define fFS6    42
#define fF6     43
#define fE6     44
#define fEF6    45
#define fDS6    46
#define fD6     47
#define fDF6    48
#define fCS6    49
#define fC6     50

#define fB5     51
#define fBF5    52
#define fAS5    53
#define fA5     54
#define fAF5    55
#define fGS5    56
#define fG5     57
#define fGF5    58
#define fFS5    59
#define fF5     60
#define fE5     61
#define fEF5    62
#define fDS5    63
#define fD5     64
#define fDF5    65
#define fCS5    66
#define fC5     67

#define fB4     68
#define fBF4    69
#define fAS4    70
#define fA4     71
#define fAF4    72
#define fGS4    73
#define fG4     74
#define fGF4    75
#define fFS4    76
#define fF4     77
#define fE4     78
#define fEF4    79
#define fDS4    80
#define fD4     81
#define fDF4    82
#define fCS4    83
#define fC4     84

#define fB3     85
#define fBF3    86
#define fAS3    87
#define fA3     88
#define fAF3    89
#define fGS3    90
#define fG3     91
#define fGF3    92
#define fFS3    93
#define fF3     94
#define fE3     95
#define fEF3    96
#define fDS3    97
#define fD3     98
#define fDF3    99
#define fCS3    100
#define fC3     101

#define fB2     102
#define fBF2    103
#define fAS2    104
#define fA2     105
#define fAF2    106
#define fGS2    107
#define fG2     108
#define fGF2    109
#define fFS2    110
#define fF2     111
#define fE2     112
#define fEF2    113
#define fDS2    114
#define fD2     115
#define fDF2    116
#define fCS2    117
#define fC2     118

#define fB1     119
#define fBF1    120
#define fAS1    121
#define fA1     122
#define fAF1    123
#define fGS1    124
#define fG1     125
#define fGF1    126
#define fFS1    127
#define fF1     128
#define fE1     129
#define fEF1    130
#define fDS1    131
#define fD1     132
#define fDF1    133
#define fCS1    134
#define fC1     135

#define fB0     136
#define fBF0    137
#define fAS0    138
#define fA0     139
#define fAF0    140
#define fGS0    141
#define fG0     142
#define fGF0    143
#define fFS0    144
#define fF0     145
#define fE0     146
#define fEF0    147
#define fDS0    148
#define fD0     149
#define fDF0    150
#define fCS0    151
#define fC0     152

#define fREST   153

/* (descending) tone values : { name, freq, level, type } */
static MusicTone TONES[] = {
{ "B8",    7902,  63,   "=" },  // fB8  - 7902.13
{ "Bb8",   7459,  63,   "-" },  // fBF8 - 7458.62
{ "A#8",   7459,  62,   "+" },  // fAS8 - 7458.62
{ "A8",    7040,  62,   "=" },  // fA8  - 7040.00
{ "Ab8",   6645,  62,   "-" },  // fAF8 - 6644.88
{ "G#8",   6645,  61,   "+" },  // fGS8 - 6644.88
{ "G8",    6272,  61,   "=" },  // fG8  - 6271.93
{ "Gb8",   5920,  61,   "-" },  // fGF8 - 5919.91
{ "F#8",   5920,  60,   "+" },  // fFS8 - 5919.91
{ "F8",    5588,  60,   "=" },  // fF8  - 5587.65
{ "E8",    5274,  59,   "=" },  // fE8  - 5274.04
{ "Eb8",   4978,  59,   "-" },  // fEF8 - 4978.03
{ "D#8",   4978,  58,   "+" },  // fDS8 - 4978.03
{ "D8",    4699,  58,   "=" },  // fD8  - 4698.63
{ "Db8",   4435,  58,   "-" },  // fDF8 - 4434.92
{ "C#8",   4435,  57,   "+" },  // fCS8 - 4434.92
{ "C8",    4186,  57,   "=" },  // fC8  - 4186.01- HIGHEST PIANO KEY

{ "B7",    3951,  56,   "=" },  // fB7  - 3951.07
{ "Bb7",   3729,  56,   "-" },  // fBF7 - 3729.31
{ "A#7",   3729,  55,   "+" },  // fAS7 - 3729.31
{ "A7",    3520,  55,   "=" },  // fA7  - 3520.00
{ "Ab7",   3322,  55,   "-" },  // fAF7 - 3322.44
{ "G#7",   3322,  54,   "+" },  // fGS7 - 3322.44
{ "G7",    3136,  54,   "=" },  // fG7  - 3135.96
{ "Gb7",   2960,  54,   "-" },  // fGF7 - 2959.96
{ "F#7",   2960,  53,   "+" },  // fFS7 - 2959.96
{ "F7",    2794,  53,   "=" },  // fF7  - 2793.83
{ "E7",    2637,  52,   "=" },  // fE7  - 2637.02
{ "Eb7",   2489,  52,   "-" },  // fEF7 - 2489.02
{ "D#7",   2489,  51,   "+" },  // fDS7 - 2489.02
{ "D7",    2349,  51,   "=" },  // fD7  - 2349.32
{ "Db7",   2217,  51,   "-" },  // fDF7 - 2217.46
{ "C#7",   2217,  50,   "+" },  // fCS7 - 2217.46
{ "C7",    2093,  50,   "=" },  // fC7  - 2093.00

{ "B6",    1976,  49,   "=" },  // fB6  - 1975.53
{ "Bb6",   1865,  49,   "-" },  // fBF6 - 1864.66
{ "A#6",   1865,  48,   "+" },  // fAS6 - 1864.66
{ "A6",    1760,  48,   "=" },  // fA6  - 1760.00
{ "Ab6",   1661,  48,   "-" },  // fAF6 - 1661.22
{ "G#6",   1661,  47,   "+" },  // fGS6 - 1661.22
{ "G6",    1568,  47,   "=" },  // fG6  - 1567.98
{ "Gb6",   1480,  47,   "-" },  // fGF6 - 1479.98
{ "F#6",   1480,  46,   "+" },  // fFS6 - 1479.98
{ "F6",    1397,  46,   "=" },  // fF6  - 1396.91
{ "E6",    1319,  45,   "=" },  // fE6  - 1318.51
{ "Eb6",   1245,  45,   "-" },  // fEF6 - 1244.51
{ "D#6",   1245,  44,   "+" },  // fDS6 - 1244.51
{ "D6",    1175,  44,   "=" },  // fD6  - 1174.66
{ "Db6",   1109,  44,   "-" },  // fDF6 - 1108.73
{ "C#6",   1109,  43,   "+" },  // fCS6 - 1108.73
{ "C6",    1047,  43,   "=" },  // fC6  - 1046.50

{ "B5",    988,   42,   "=" },  // fB5  - 987.77
{ "Bb5",   932,   42,   "-" },  // fBF5 - 932.33
{ "A#5",   932,   41,   "+" },  // fAS5 - 932.33
{ "A5",    880,   41,   "=" },  // fA5  - 880.00
{ "Ab5",   831,   41,   "-" },  // fAF5 - 830.61
{ "G#5",   831,   40,   "+" },  // fGS5 - 830.61
{ "G5",    784,   40,   "=" },  // fG5  - 783.99
{ "Gb5",   740,   40,   "-" },  // fGF5 - 739.99
{ "F#5",   740,   39,   "+" },  // fFS5 - 739.99
{ "F5",    698,   39,   "=" },  // fF5  - 698.46 - treble clef
{ "E5",    659,   38,   "=" },  // fE5  - 659.25
{ "Eb5",   622,   38,   "-" },  // fEF5 - 622.25
{ "D#5",   622,   37,   "+" },  // fDS5 - 622.25
{ "D5",    587,   37,   "=" },  // fD5  - 587.33 - treble clef
{ "Db5",   554,   37,   "-" },  // fDF5 - 554.37
{ "C#5",   554,   36,   "+" },  // fCS5 - 554.37
{ "C5",    523,   36,   "=" },  // fC5  - 523.25

{ "B4",    494,   35,   "=" },  // fB4  - 493.88 - treble clef
{ "Bb4",   466,   35,   "-" },  // fBF4 - 466.16
{ "A#4",   466,   34,   "+" },  // fAS4 - 466.16
{ "A4",    440,   34,   "=" },  // fA4  - 440.00 - base frequency
{ "Ab4",   415,   34,   "-" },  // fAF4 - 415.30
{ "G#4",   415,   33,   "+" },  // fGS4 - 415.30
{ "G4",    392,   33,   "=" },  // fG4  - 392.00 - treble clef
{ "Gb4",   370,   33,   "-" },  // fGF4 - 369.99
{ "F#4",   370,   32,   "+" },  // fFS4 - 369.99
{ "F4",    349,   32,   "=" },  // fF4  - 349.23
{ "E4",    330,   31,   "=" },  // fE4  - 329.63 - treble clef - fE4,fG4,fB4,fD5,fF5
{ "Eb4",   311,   31,   "-" },  // fEF4 - 311.13
{ "D#4",   311,   30,   "+" },  // fDS4 - 311.13
{ "D4",    294,   30,   "=" },  // fD4  - 293.66
{ "Db4",   277,   30,   "-" },  // fDF4 - 277.18
{ "C#4",   277,   29,   "+" },  // fCS4 - 277.18
{ "C4",    262,   29,   "=" },  // fC4  - 261.63 - MIDDLE C

{ "B3",    247,   28,   "=" },  // fB3  - 246.94
{ "Bb3",   233,   28,   "-" },  // fAS3 - 233.08
{ "A#3",   233,   27,   "+" },  // fAS3 - 233.08
{ "A3",    220,   27,   "=" },  // fA3  - 220.00 - base clef - fG2,fB2,fD3,fF3,fA3
{ "Ab3",   208,   27,   "-" },  // fAF3 - 207.65
{ "G#3",   208,   26,   "+" },  // fGS3 - 207.65
{ "G3",    196,   26,   "=" },  // fG3  - 196.00
{ "Gb3",   185,   26,   "-" },  // fGF3 - 185.00
{ "F#3",   185,   25,   "+" },  // fFS3 - 185.00
{ "F3",    175,   25,   "=" },  // fF3  - 174.61 - base clef
{ "E3",    165,   24,   "=" },  // fE3  - 164.81
{ "Eb3",   156,   24,   "-" },  // fEF3 - 155.56
{ "D#3",   156,   23,   "+" },  // fDS3 - 155.56
{ "D3",    147,   23,   "=" },  // fD3  - 146.83 - base clef
{ "Db3",   139,   23,   "-" },  // fDF3 - 138.59
{ "C#3",   139,   22,   "+" },  // fCS3 - 138.59
{ "C3",    131,   22,   "=" },  // fC3  - 130.81

{ "B2",    123,   21,   "=" },  // fB2  - 123.47 - base clef
{ "Bb2",   117,   21,   "-" },  // fBF2 - 116.54
{ "A#2",   117,   20,   "+" },  // fAS2 - 116.54
{ "A2",    110,   20,   "=" },  // fA2  - 110.00
{ "Ab2",   104,   20,   "-" },  // fAF2 - 103.83
{ "G#2",   104,   19,   "+" },  // fGS2 - 103.83
{ "G2",    98,    19,   "=" },  // fG2  - 98.00  - base clef
{ "Gb2",   93,    19,   "-" },  // fGF2 - 92.50
{ "F#2",   93,    18,   "+" },  // fFS2 - 92.50
{ "F2",    87,    18,   "=" },  // fF2  - 87.31
{ "E2",    82,    17,   "=" },  // fE2  - 82.41
{ "Eb2",   78,    17,   "-" },  // fEF2 - 77.78
{ "D#2",   78,    16,   "+" },  // fDS2 - 77.78
{ "D2",    73,    16,   "=" },  // fD2  - 73.42
{ "Db2",   69,    16,   "-" },  // fDF2 - 69.30
{ "C#2",   69,    15,   "+" },  // fCS2 - 69.30
{ "C2",    65,    15,   "=" },  // fC2  - 65.41

{ "B1",    62,    14,   "=" },  // fB1  - 61.74
{ "Bb1",   58,    14,   "-" },  // fBF1 - 58.27
{ "A#1",   58,    13,   "+" },  // fAS1 - 58.27
{ "A1",    55,    13,   "=" },  // fA1  - 55.00
{ "Ab1",   52,    13,   "-" },  // fAF1 - 51.91
{ "G#1",   52,    12,   "+" },  // fGS1 - 51.91
{ "G1",    49,    12,   "=" },  // fG1  - 49.00
{ "Gb1",   46,    12,   "-" },  // fGF1 - 46.25
{ "F#1",   46,    11,   "+" },  // fFS1 - 46.25
{ "F1",    44,    11,   "=" },  // fF1  - 43.65
{ "E1",    41,    10,   "=" },  // fE1  - 41.20
{ "Eb1",   39,    10,   "-" },  // fEF1 - 38.89
{ "D#1",   39,    9,    "+" },  // fDS1 - 38.89
{ "D1",    37,    9,    "=" },  // fD1  - 36.71
{ "Db1",   25,    9,    "-" },  // fDF1 - 34.65
{ "C#1",   25,    8,    "+" },  // fCS1 - 34.65
{ "C1",    33,    8,    "=" },  // fC1  - 32.70

{ "B0",    31,    7,    "=" },  // fB0  - 30.87 - B
{ "Bb0",   29,    7,    "-" },  // fBF0 - 29.14 - A#/Bb
{ "A#0",   29,    6,    "+" },  // fAS0 - 29.14 - A#/Bb
{ "A0",    28,    6,    "=" },  // fA0  - 27.50 - A     - LOWEST PIANO KEY
{ "Ab0",   26,    6,    "-" },  // fAF0 - 25.96 - G#/Ab
{ "G#0",   26,    5,    "+" },  // fGS0 - 25.96 - G#/Ab
{ "G0",    25,    5,    "=" },  // fG0  - 24.50 - G
{ "Gb0",   23,    5,    "-" },  // fGF0 - 23.12 - F#/Gb
{ "F#0",   23,    4,    "+" },  // fFS0 - 23.12 - F#/Gb
{ "F0",    22,    4,    "=" },  // fF0  - 21.83 - F
{ "E0",    21,    3,    "=" },  // fE0  - 20.60 - E
{ "Eb0",   19,    3,    "-" },  // fEF0 - 19.45 - D#/Eb
{ "D#0",   19,    2,    "+" },  // fDS0 - 19.45 - D#/Eb
{ "D0",    18,    2,    "=" },  // fD0  - 18.35 - D
{ "Db0",   17,    2,    "-" },  // fDF0 - 17.32 - C#/Db
{ "C#0",   17,    1,    "+" },  // fCS0 - 17.32 - C#/Db
{ "C0",    16,    1,    "=" },  // fC0  - 16.35 - C

{ "REST",  0,     0,    "=" },  // fREST
};


// SCALES
// C-major : C4,  D4,  E4,  F4,  G4,  A4,  B4, C5 : -
// G-major : G4,  A4,  B4,  C5,  D5,  E5, FS5, G5 : #:F
// D-major : D4,  E4, FS4,  G4,  A4,  B4, CS5, D5 : #:FC 
// A-major : A4,  B4, CS5,  D5,  E5, FS5, GS5, A5 : #:FCG
// E-major : E4, FS4, GS4,  A4,  B4, CS5, DS5, E5 : #:FCGD
// B-major : B4, CS5, DS5,  E5, FS5, GS5, AS5, B5 : #:FCGDA
// F-major : F4,  G4,  A4, BF4,  C5,  D5,  E5, F5 : b:B

// A-minor : A4,  B4,  C5,  D5,  E5,  F5, GS5, A5 : -
// E-minor : E4, FS4,  G4,  A4,  B4,  C5, DS5, E5 : #:F
// B-minor : B4, CS5,  D5,  E5, FS5,  G5, AS5, B5 : #:FC
// F-minor : F4,  G4, AF4, BF4,  C5, DF5,  E5, F5 : b:BEAD
// C-minor : C4,  D4, EF4,  F4,  G4, AF4,  B4, C5 : b:BEA
// G-minor : G4,  A4, BF4,  C5,  D5, EF5, FS5, G5 : b:BE
// D-minor : D4,  E4,  F4,  G4,  A4, BF4, CS5, D5 : b:B 

// C-blues : C4,  D#4,  F4,  FS4,  G4, BF4, B4, C5 : -

// PROGRESSIONS  : CHORDS
// I-IV-V        : C-F-G    - standard/blues
// I–V–vi–IV     : C-G-Am-F - sensitive
// ii–V–I        : Dm-G-C   - jazz
// I–vi–IV–V     : C-Am-F-G
// I–IV–V–IV     : C-F-G-F
// vi–IV–I–V     : Am-F-C-G
// I–IV–ii–V     : C-F-Dm-G
// I–IV–I–V      : C-F-C-G
// I–ii–iii–IV–V : C-Dm-Em-F-G
// I–III–IV–iv   : C-E-F-?
// i–V–i–iv      : A-G-?-?
// vi–V–IV–III   : Am-G-F-E - andalusian
// I–V–vi–iii–IV–I–IV–V : C-G-Am-Em-F-C-F-G - canon

// CIRCLE OF FIFTHS : 4b-1b | C | 1#-4# | 5#/7b, 6#/6b, 7#/5b
// major:  ?=Ab, ?=Eb, ?=Bb, IV=F  |  I=C  |   V=G,   II=D,  VI=A,  III=E   | VII=B/Cb,    ?=F#/Gb,   ?=C#/Db   | 
// minor: iv=Fm, i=Cm, v=Gm, ii=Dm | vi=Am | iii=Em, vii=Bm,  ?=F#m,  ?=C#m |   ?=G#m/Abm, ?=D#m/Ebm, ?=A#m/Bbm | 

// CHORDS
// C:    C, E, G
// Cm:   C, Eb, G
// Cdim: C, Eb, Gb
// Caug: C, E, G#
// C7:   C, E, G, Bb
