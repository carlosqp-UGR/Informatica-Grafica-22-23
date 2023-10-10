#ifndef _PLY_REVOLUTION_OBJECT_H
#define _PLY_REVOLUTION_OBJECT_H

#include "ply_object.h"
#include "revolution_object.h"

/**
 * @brief The _ply_revolution_object class
 * Combines both funcionalities from its two fathers.
 * Creates an object from a profile read in a ply file.
 */
class _ply_revolution_object : public _ply_object, public _revolution_object
{
public:

    /**
     * @brief _ply_revolution_object class constructor
     * @param n natural number of profiles generated
     * @param file_name ply file with profile data
     */
    _ply_revolution_object(int n=36, const string &file_name = "../ply_models/ply_revolution_profiles/example.ply");

};

#endif // _PLY_REVOLUTION_OBJECT_H
