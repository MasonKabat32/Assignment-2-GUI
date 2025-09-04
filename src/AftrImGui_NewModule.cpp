#include "AftrImGui_NewModule.h"
#include "AftrImGuiIncludes.h"
#include <fmt/core.h>
#include <chrono>

void Aftr::AftrImGui_NewModule::draw(WO* &plane, bool& sphereFlag, bool& sphereRemovalFlag)
{
   this->draw_orbit_controls();
   this->plane = plane;
   this->sphereFlag = &sphereFlag; 
   this->sphereRemovalFlag = &sphereRemovalFlag;
}

void Aftr::AftrImGui_NewModule::draw_orbit_controls() //GUI elements will go into this function here
{
   if( ImGui::Begin( "Assignment 2 GUI" ) )
   {
      /*if( ImGui::Button( ( this->isPaused ? "Resume Motion" : "Pause Motion" ) ) )
      {
         this->isPaused = !this->isPaused;
         if( this->isPaused )
            this->pause_time = std::chrono::system_clock::now();
         else
            this->start_time = (std::chrono::system_clock::now() - pause_time) + start_time;
         fmt::print( "Moon Orbiter Status: {:b}...\n", this->isPaused );
      }*/

       if (ImGui::SliderInt("Slide Plane Along X axis", &this->distance_from_origin, -500, 500))
       {
            fmt::print( "Adjusted plane distance from origin Good job...\n", this->distance_from_origin );
            if (this->plane != nullptr) { //Double check that plane is not null
                this->plane->setPosition(Vector(this->distance_from_origin, 0, 25));
            }
           
       }

       if (ImGui::SliderFloat("Bank Plane", &this->orientation, -100, 100)) { //Need to rotate in radians
           fmt::print("Adjusted plane orientation, Good job...\n", this->orientation);
           if (this->plane != nullptr) {
               this->plane->rotateAboutRelX(this->orientation);
           }
       }

       if (ImGui::SliderFloat("Rotata Plane Around Global Z", &this->globalOrientation, -100, 100)) {
           fmt::print("Rotating plane around origin...\n");
           if (this->plane != nullptr) {
               this->plane->rotateAboutGlobalZ(this->globalOrientation);
           }
       }

       if (ImGui::Button("Add a Sphere")) {
           if (this->sphereFlag != nullptr)
           {
               *this->sphereFlag = true; //flip the flag in glview
               this->sphereCount += 1;
               fmt::print("Adding a sphere");
           }
       }

       if (ImGui::Button("Get Rid of a Sphere")) {
           if (this->sphereCount > 0 && this->sphereRemovalFlag != nullptr) {
               this->sphereCount -= 1;
               *this->sphereRemovalFlag = true;
           }
       }

/*      if( ImGui::SliderInt( "Orbit time (msec)", &this->orbitTime_msec, 50, 10000 ) )
         fmt::print( "Adjusted Moon Orbiter time to {:d} milliseconds... Better job...\n", this->orbitTime_msec )*/;

      ImGui::End();
   }
}

//Aftr::Mat4 Aftr::AftrImGui_NewModule::compute_pose( Mat4 const& origin )
//{
//   if( !this->isPaused )
//      this->now_time = std::chrono::system_clock::now();
//
//   //one revolution completes in exactly REV_TIME, compute parametric offset based on the current time
//   std::chrono::duration REV_TIME = std::chrono::milliseconds( this->orbitTime_msec );
//
//   auto delta_t = std::chrono::duration<float>( now_time - start_time );
//   float t = float( delta_t / REV_TIME ); //parametric distance [0,1], between start time and now
//   //fmt::print( "Num revolutions is {:f}\n", t);
//
//   //Compute the pose of the orbiting object -- the position and the orientation
//   Vector pos = origin.getPosition();
//   Vector fwdVec = origin.getX();
//   Vector upVec = origin.getZ();
//   Vector orbit_pos = pos + (fwdVec * distance_between).rotate( upVec, t * Aftr::PI * 2.0f );
//   Vector relX = (pos - orbit_pos).normalizeMe();
//   Vector relY = upVec.crossProduct( relX );
//   Vector relZ = relX.crossProduct( relY );
//   Mat4 pose( relX, relY, relZ );
//   pose.setPosition( orbit_pos );
//   return pose;
//}