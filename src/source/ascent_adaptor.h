#pragma once

//#include "sph/particles_data.hpp"
#include <ascent/ascent.hpp>
#include "conduit_blueprint.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

namespace AscentAdaptor
{
ascent::Ascent a;
conduit::Node  actions;

//{{{ viz::Initialize
//template<class DataType>
void Initialize()
//void Initialize([[maybe_unused]] DataType& d, [[maybe_unused]] long startIndex)
{
    conduit::Node ascent_options;
    // ascent_options["default_dir"] = "/scratch/snx3000/jfavre/DummySPH/datasets";
    // ascent_options["mpi_comm"] = MPI_Comm_c2f(MPI_COMM_WORLD);
    a.open(ascent_options);
//{{{
//del     // Create an action that tells Ascent to:
//del     //  add a scene (s1) with one plot (p1)
//del     //  that will render a pseudocolor of
//del     //  the mesh field `rho`
//del 
//del     conduit::Node& add_pipe      = actions.append();
//del     add_pipe["action"]           = "add_pipelines";
//del     conduit::Node& pipes         = add_pipe["pipelines"];
//del     pipes["pl1/f1/type"]         = "threshold";
//del     conduit::Node& thresh_params = pipes["pl1/f1/params"];
//del     thresh_params["field"]       = "Density";
//del     thresh_params["min_value"]   = 1.4;
//del     thresh_params["max_value"]   = 2000;
//del 
//del     conduit::Node& add_scene = actions.append();
//del     add_scene["action"]      = "add_scenes";
//del 
//del     // declare a scene (s1) and pseudocolor plot (p1)
//del     conduit::Node& scenes          = add_scene["scenes"];
//del     scenes["s1/plots/p1/type"]     = "pseudocolor";
//del     //scenes["s1/plots/p1/pipeline"] = "pl1";
//del     scenes["s1/plots/p1/field"]    = "Density";
//del     // scenes["s1/plots/p1/points/radius"] = .5;
//del     // scenes["s1/plots/p1/points/radius_delta"] = .01;
//del     scenes["s1/renders/r1/image_prefix"] = "DensityThreshold1.4.%05d";
//del 
//del     double vec3[3];
//del     vec3[0] = vec3[1] = vec3[2] = 0;
//del     scenes["s1/renders/r1/camera/look_at"].set_float64_ptr(vec3, 3);
//del 
//del     vec3[0] = -2.1709899968205337;
//del     vec3[1] = 1.797907520678797;
//del     vec3[2] = 1.8029059671481107;
//del     scenes["s1/renders/r1/camera/position"].set_float64_ptr(vec3, 3);
//del 
//del     vec3[0] = 0.4479257557058854;
//del     vec3[1] = 0.8420981185224633;
//del     vec3[2] = -0.30038854198560727;
//del     scenes["s1/renders/r1/camera/up"].set_float64_ptr(vec3, 3);
//del     scenes["s1/renders/r1/camera/zoom"] = 2;
//del 
//del     /*
//del     scenes["s1/renders/r1/type"] = "cinema";
//del     scenes["s1/renders/r1/phi"] = 8;
//del     scenes["s1/renders/r1/theta"] = 8;
//del     scenes["s1/renders/r1/db_name"] = "example_db";
//del     */
//del 
//del     /* IO to disk */
//del     conduit::Node& add_extr = actions.append();
//del     add_extr["action"]      = "add_extracts";
//del     conduit::Node& savedata = add_extr["extracts"];
//del 
//del     // add a relay extract that will write mesh data to
//del     // blueprint hdf5 files
//del     savedata["e1/type"] = "relay";
//del     // savedata["e1/pipeline"] = "pl1";
//del     savedata["e1/params/path"]     = "out_export_particles";
//del     savedata["e1/params/protocol"] = "hdf5";
//del     //actions.to_yaml();
//}}}
}
//}}}

//{{{ addField
//todo template<class FieldType>
//todo void addField(conduit::Node& mesh, const std::string& name, FieldType* field, size_t start, size_t end)
//todo {
//todo     mesh["fields/" + name + "/association"] = "vertex";
//todo     mesh["fields/" + name + "/topology"]    = "mesh";
//todo     mesh["fields/" + name + "/values"].set_external(field + start, end - start);
//todo     mesh["fields/" + name + "/volume_dependent"].set("false");
//todo }
//}}}

//{{{ viz::Execute
void Execute(
        JDataArrays& arrays2,
        //long array2_count,
        double TimeStep)
//void Execute(long array2_count)
{
    conduit::Node mesh;
    long array2_count = arrays2.Arrays[0].count;
    tfloat3* f3Ptr = static_cast<tfloat3*>(arrays2.Arrays[0].ptr); // !
    float*    fPtr = static_cast<float*>(arrays2.Arrays[3].ptr); // !
    //del std::cout << "### A:array2_count=" << arrays2.Arrays[0].count << "\n";
    //del std::cout << "### B:array2_count=" << array2_count << "\n";
    //del std::cout << f3Ptr[0].x << "\n";
    //auto array2_count = arrays2.Arrays[0].count;
//todo       conduit::Node mesh;
//todo       auto array2_count = arrays2.Arrays[0].count;
    mesh["state/cycle"].set(TimeStep);
    mesh["state/time"].set(TimeStep);
    mesh["coordsets/coords/type"] = "explicit";
    //mesh["coordsets/coords/values/x"].set_external(&f3Ptr[0].x, array2_count);
    mesh["coordsets/coords/values/x"].set_external(&f3Ptr[0].x, array2_count);
    mesh["coordsets/coords/values/y"].set_external(&f3Ptr[0].y, array2_count);
    mesh["coordsets/coords/values/z"].set_external(&f3Ptr[0].z, array2_count);
    mesh["topologies/mesh/type"] = "points";
    mesh["topologies/mesh/coordset"] = "coords";
    // x
    mesh["fields/x/association"] = "vertex";
    mesh["fields/x/topology"] = "mesh";
    //mesh["fields/x/values"].set_external(&f3Ptr[0].x, array2_count);
    mesh["fields/x/values"].set_external(&f3Ptr[0].x, array2_count);
    mesh["fields/x/volume_dependent"].set("false");
    // y
    mesh["fields/y/association"] = "vertex";
    mesh["fields/y/topology"] = "mesh";
    mesh["fields/y/values"].set_external(&f3Ptr[0].y, array2_count);
    mesh["fields/y/volume_dependent"].set("false");
    // z
    mesh["fields/z/association"] = "vertex";
    mesh["fields/z/topology"] = "mesh";
    mesh["fields/z/values"].set_external(&f3Ptr[0].z, array2_count);
    mesh["fields/z/volume_dependent"].set("false");
    // [0] Pos  TypeFloat3
    // [1] Idp  TypeUint
    // [2] Vel  TypeFloat3
    // [3] Rhop TypeFloat
    // [4] Type TypeUchar
    mesh["fields/rhop/association"] = "vertex";
    mesh["fields/rhop/topology"] = "mesh";
    mesh["fields/rhop/values"].set_external(&fPtr[0], array2_count);
    mesh["fields/rhop/volume_dependent"].set("false");
    // ./DualSPHysics5.2CPU_linux64 ${dirout}/${name} ${dirout} -dirdataout data -svres -sv:vtk
    conduit::Node verify_info;
    if (!conduit::blueprint::mesh::verify(mesh, verify_info)) {
      CONDUIT_INFO("blueprint verify failed!" + verify_info.to_json());
    // } else {
    //   CONDUIT_INFO("blueprint verify success!" + verify_info.to_json());
    }
    a.publish(mesh);
    a.execute(actions);
}
//sphexa template<class DataType>
//sphexa void Execute(DataType& d, long startIndex, long endIndex)
//sphexa {
//sphexa     conduit::Node mesh;
//sphexa     mesh["state/cycle"].set_external(&d.iteration);
//sphexa     mesh["state/time"].set_external(&d.ttot);
//sphexa 
//sphexa     mesh["coordsets/coords/type"] = "explicit";
//sphexa     mesh["coordsets/coords/values/x"].set_external(d.x.data() + startIndex, endIndex - startIndex);
//sphexa     mesh["coordsets/coords/values/y"].set_external(d.y.data() + startIndex, endIndex - startIndex);
//sphexa     mesh["coordsets/coords/values/z"].set_external(d.z.data() + startIndex, endIndex - startIndex);
//sphexa 
//sphexa     mesh["topologies/mesh/type"] = "points";
//sphexa     mesh["topologies/mesh/coordset"] = "coords";
//sphexa 
//sphexa     addField(mesh, "x", d.x.data(), startIndex, endIndex);
//sphexa     addField(mesh, "y", d.y.data(), startIndex, endIndex);
//sphexa     addField(mesh, "z", d.z.data(), startIndex, endIndex);
//sphexa     addField(mesh, "vx", d.vx.data(), startIndex, endIndex);
//sphexa     addField(mesh, "vy", d.vy.data(), startIndex, endIndex);
//sphexa     addField(mesh, "vz", d.vz.data(), startIndex, endIndex);
//sphexa     addField(mesh, "Mass", d.m.data(), startIndex, endIndex);
//sphexa     addField(mesh, "Smoothing Length", d.h.data(), startIndex, endIndex);
//sphexa     addField(mesh, "Density", d.rho.data(), startIndex, endIndex);
//sphexa     addField(mesh, "Internal Energy", d.u.data(), startIndex, endIndex);
//sphexa     addField(mesh, "Pressure", d.p.data(), startIndex, endIndex);
//sphexa     addField(mesh, "Speed of Sound", d.c.data(), startIndex, endIndex);
//sphexa     addField(mesh, "ax", d.ax.data(), startIndex, endIndex);
//sphexa     addField(mesh, "ay", d.ay.data(), startIndex, endIndex);
//sphexa     addField(mesh, "az", d.az.data(), startIndex, endIndex);
//sphexa 
//sphexa 
//sphexa 
//sphexa     conduit::Node verify_info;
//sphexa     if (!conduit::blueprint::mesh::verify(mesh, verify_info))
//sphexa     {
//sphexa         // verify failed, print error message
//sphexa         CONDUIT_INFO("blueprint verify failed!" + verify_info.to_json());
//sphexa     }
//sphexa     // else CONDUIT_INFO("blueprint verify success!" + verify_info.to_json());
//sphexa 
//sphexa     a.publish(mesh);
//sphexa     a.execute(actions);
//sphexa }
//}}}

//{{{ viz::Finalize
void Finalize() { a.close(); }
//}}}

} // namespace AscentAdaptor
