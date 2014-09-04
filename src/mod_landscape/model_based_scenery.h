/*
 * CRRCsim - the Charles River Radio Control Club Flight Simulator Project
 *
 *   Copyright (C) 2000, 2001 Jan Kansky (original author)
 *   Copyright (C) 2004-2010 Jan Reucker
 *   Copyright (C) 2005, 2008 Jens Wilhelm Wulf
 *   Copyright (C) 2009 Joel Lienard
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef MODEL_BASED_SCENERY_H
#define MODEL_BASED_SCENERY_H

#include <crrc_config.h>

#include "crrc_scenery.h"
#include "../mod_math/vector3.h"
#include "../mod_misc/SimpleXMLTransfer.h"
#include <plib/ssg.h>
#include "winddata3D.h"
#include "heightdata.h"


#define SIZE_GRID_PLANES 150
#define SIZE_CELL_GRID_PLANES 20


/**
 *  \brief Class for 3D-model-based sceneries
 *
 */
class ModelBasedScenery : public Scenery
{
  public:
    /**
     *  The constructor
     *
     *  \param xml SimpleXMLTransfer from which the base classes will be initialized
     */
    ModelBasedScenery(SimpleXMLTransfer *xml, int sky_variant);
  
    /**
     *  The destructor
     */
    ~ModelBasedScenery();
  
    /**
     *  Draw the scenery
     */
    void draw(double current_time);


    /**
     *  Get the height at a distinct point.
     *  \param x x coordinate
     *  \param z z coordinate
     *  \return terrain height at this point in ft
     */
    float getHeight(float x, float z);


    /**
     *  get height and plane equation at x|z
     *  \param x x coordinate
     *  \param z z coordinate
     *  \param tplane this is where the plane equation will be stored
     *  \return terrain height at this point in ft
     */
    float getHeightAndPlane(float x, float z, float tplane[4]);
    
    /**
     *  Get an ID code for this location or scenery type
     */
    int getID() {return location;};
    /*
  get  wind on  directions  at position  X_cg, Y_cg,Z_cg
  */
    void getWindComponents(double X_cg,double  Y_cg,double  Z_cg,
      float  *x_wind_velocity, float  *y_wind_velocity, float  *z_wind_velocity);
    /**/
  
  private:
    int   location;   ///< location id
    ssgRoot       *SceneGraph;
    ssgTransform  *initial_trans;
    int getHeight_mode;
      //0 :  use ssgLOS ( slow if many triangle)
      //1 :  ssgLOS()s en table (not god)
      //2 : Tiling of surface 
      

    HeightData *heightdata;

    void make_tab_HeightAndPlane(); 
    float tab_HeightAndPlane [SIZE_GRID_PLANES+1][SIZE_GRID_PLANES+1][4];
    float tab_HOT [SIZE_GRID_PLANES+1][SIZE_GRID_PLANES+1];
    float getHeightAndPlane_(float x, float z, float tplane[4]);
    void  setToInvisibleState(ssgEntity* ent);
    void  evaluateNodeAttributes(ssgEntity* ent);
  #if WINDDATA3D == 1
    int init_wind_data(const char* filename);
    int find_wind_data(float n,float e,float u, float *vx, float *vy, float * vz);
    WindData  * wind_data;
#endif
    float wind_position_coef;
    
    ssgSimpleState *invisible_state;
};


#endif  // MODEL_BASED_SCENERY_H
