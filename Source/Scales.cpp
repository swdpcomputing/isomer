#include "Scales.h"

    //-----SCALE TYPES-----\\

Scales::Scales()
{
    scaleArray.add (new Scale ("Chromatic",                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    scaleArray.add (new Scale ("Major",                     2, 2, 1, 2, 2, 2, 1));
    scaleArray.add (new Scale ("Minor",                     2, 1, 2, 2, 1, 2, 2));
    scaleArray.add (new Scale ("Pentatonic Major",          2, 2, 3, 2, 3));
    scaleArray.add (new Scale ("Pentatonic Minor",          3, 2, 2, 3, 2));
    scaleArray.add (new Scale ("Ionian",                    2, 2, 1, 2, 2, 2, 1));
    scaleArray.add (new Scale ("Dorian",                    2, 1, 2, 2, 2, 2, 2));
    scaleArray.add (new Scale ("Phyrigian",                 1, 2, 2, 2, 1, 2, 2));
    scaleArray.add (new Scale ("Lydian",                    2, 2, 2, 1, 2, 2, 1));
    scaleArray.add (new Scale ("MixoLydian",                2, 2, 1, 2, 2, 1, 2));
    scaleArray.add (new Scale ("Aeolian",                   2, 1, 2, 2, 1, 2, 2));
    scaleArray.add (new Scale ("Locrian",                   1, 2, 2, 1, 2, 2, 2));
    scaleArray.add (new Scale ("Melodic Minor",             2, 1, 2, 2, 2, 2, 1));
    scaleArray.add (new Scale ("MM2 - Phygian Nat6",        1, 2, 2, 2, 2, 1, 2));
    scaleArray.add (new Scale ("MM3 - Lydian #5",           2, 2, 2, 2, 1, 2, 1));
    scaleArray.add (new Scale ("MM4 - Lydian Dom",          2, 2, 2, 1, 2, 1, 2));
    scaleArray.add (new Scale ("MM5 - Aeolian Nat",         2, 2, 1, 2, 1, 2, 2));
    scaleArray.add (new Scale ("MM6 - Locrian Nat",         2, 1, 2, 1, 2, 2, 2));
    scaleArray.add (new Scale ("MM7 - Altered Scale",       1, 2, 1, 2, 2, 2, 2));
    scaleArray.add (new Scale ("Harmonic Minor",            2, 1, 2, 2, 1, 3, 1));
    scaleArray.add (new Scale ("HM2 - Locrian #6",          1, 2, 2, 1, 3, 1, 2));
    scaleArray.add (new Scale ("HM3 - Ionian #5",           2, 2, 1, 3, 1, 2, 1));
    scaleArray.add (new Scale ("HM4 - Dorian #4",           2, 1, 3, 1, 2, 1, 2));
    scaleArray.add (new Scale ("HM5 - Phrygian Dom",        1, 3, 1, 2, 1, 2, 2));
    scaleArray.add (new Scale ("HM6 - Lydian #2",           3, 1, 2, 1, 2, 2, 1));
    scaleArray.add (new Scale ("HM7 - Super Locrian bb7",   1, 2, 1, 2, 2, 1, 3));
    scaleArray.add (new Scale ("Enigmatic",                 1, 3, 2, 2, 2, 1, 1));
    scaleArray.add (new Scale ("Whole Tone",                2, 2, 2, 2, 2, 2));
    scaleArray.add (new Scale ("Octotonic H",               1, 2, 1, 2, 1, 2, 1, 2));
    scaleArray.add (new Scale ("Octotonic W",               2, 1, 2, 1, 2, 1, 2, 1));
    scaleArray.add (new Scale ("Blues Hex",                 3, 2, 1, 1, 3, 2));
    
    for (auto o : scaleArray) scaleIds.add (o->getScaleId());
}

Scales::~Scales()
{
    scaleArray.clear (true);
}

const Array <int>& Scales::getScale (const String a)
{
    for (auto o : scaleArray)
    {
        if (o->getScaleId() == a) return o->getScale();
    };
    
    return scaleArray.getUnchecked (0)->getScale();
}

const StringArray& Scales::getScaleIds()
{
    return scaleIds;
}

    //-----GETTERS-----\\

const StringArray& Scales::getKeyIDs()
{
    return keyIds;
}

const StringArray& Scales::getMidiNoteNumbers()
{
    return midiNoteNumbers;
}

const StringArray& Scales::getMidiNoteIDs()
{
    return midiNoteIDs;
}

    //-----SCALE TYPE-----\\

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e
                ) : scaleId (a)
{
    scaleArray.add (b);
    scaleArray.add (c);
    scaleArray.add (d);
    scaleArray.add (e);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f
                ) : Scale (a, b, c, d, e)
{
    scaleArray.add (f);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f,
                    int g
                ) : Scale (a, b, c, d, e, f)
{
    scaleArray.add (g);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f,
                    int g,
                    int h
                ) : Scale (a, b, c, d, e, f, g)
{
    scaleArray.add (h);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f,
                    int g,
                    int h,
                    int i
                ) : Scale (a, b, c, d, e, f, g, h)
{
    scaleArray.add (i);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f,
                    int g,
                    int h,
                    int i,
                    int j
                ) : Scale (a, b, c, d, e, f, g, h, i)
{
    scaleArray.add (j);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f,
                    int g,
                    int h,
                    int i,
                    int j,
                    int k
                ) : Scale (a, b, c, d, e, f, g, h, i, j)
{
    scaleArray.add (k);
}

Scale::Scale    (   String a,
                    int b,
                    int c,
                    int d,
                    int e,
                    int f,
                    int g,
                    int h,
                    int i,
                    int j,
                    int k,
                    int l
                ) : Scale (a, b, c, d, e, f, g, h, i, j, k)
{
    scaleArray.add (l);
}


Scale::~Scale()
{
}

const String Scale::getScaleId()
{
    return scaleId;
}

const Array <int>& Scale::getScale()
{
    return scaleArray;
}