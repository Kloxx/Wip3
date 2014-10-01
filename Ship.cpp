#include "Ship.h"

Ship::Ship(std::string const vertexShader, std::string const fragmentShader, std::string texture) :
    m_shader(vertexShader, fragmentShader), m_texture(texture)
{
    m_shader.charger();
    m_texture.load();
    float vertexTmp[] = {
        1.000000,-0.500000,1.000000, -1.000000,-0.500000,1.000000, -1.000000,-0.500000,-1.000000,
        -1.000000,0.500000,-1.000000, -1.000000,0.500000,1.000000, 0.999999,0.700000,1.000001,
        3.000000,0.000000,-0.999999, 1.000000,0.700000,-0.999999, 2.000000,0.600000,-0.699999,
        0.999999,0.700000,1.000001, -1.000000,0.500000,1.000000, -1.000000,0.000000,3.000000,
        1.000000,-0.500000,-1.000000, -1.000000,-0.500000,-1.000000, -1.000000,0.000000,-3.000000,
        1.000000,-0.500000,1.000000, 0.500000,0.000000,3.000000, -1.000000,0.000000,3.000000,
        1.000000,0.700000,-0.999999, 0.500000,0.000000,-3.000000, -1.000000,0.000000,-3.000000,
        3.000000,0.000000,-0.999999, 2.000000,0.600000,-0.699999, 1.999999,0.600000,0.700001,
        3.000000,0.000000,-0.999999, 0.500000,0.000000,-3.000000, 1.000000,0.700000,-0.999999,
        0.999999,0.700000,1.000001, 1.999999,0.600000,0.700001, 2.000000,0.600000,-0.699999,
        0.500000,0.000000,3.000000, 3.000000,0.000000,1.000001, 0.999999,0.700000,1.000001,
        3.000000,0.000000,1.000001, 0.500000,0.000000,3.000000, 1.000000,-0.500000,1.000000,
        -1.000000,0.000000,3.000000, -1.000000,0.500000,1.000000, -1.000000,0.400000,0.800000,
        -1.000000,0.400000,0.800000, -1.000000,0.400000,-0.800000, -1.000000,-0.400000,-0.800000,
        -1.000000,-0.400000,-0.800000, -1.000000,-0.500000,-1.000000, -1.000000,-0.500000,1.000000,
        -1.000000,0.000000,-3.000000, -1.000000,-0.500000,-1.000000, -1.000000,-0.400000,-0.800000,
        -1.000000,0.500000,-1.000000, -1.000000,0.400000,-0.800000, -1.000000,0.400000,0.800000,
        -1.000000,-0.400000,0.800000, -1.000000,-0.500000,1.000000, -1.000000,0.000000,3.000000,
        -1.000000,0.400000,-0.800000, -1.000000,0.500000,-1.000000, -1.000000,0.000000,-3.000000,
        -0.700000,0.000000,-2.400000, -0.700000,-0.400000,-0.800000, -0.700000,0.400000,-0.800000,
        -0.700000,-0.400000,-0.800000, -1.000000,-0.400000,-0.800000, -1.000000,0.400000,-0.800000,
        -0.700000,0.400000,-0.800000, -1.000000,0.400000,-0.800000, -1.000000,0.000000,-2.400000,
        -1.000000,0.000000,-2.400000, -1.000000,-0.400000,-0.800000, -0.700000,-0.400000,-0.800000,
        -1.000000,0.000000,2.400000, -1.000000,0.400000,0.800000, -0.700000,0.400000,0.800000,
        -0.700000,-0.400000,0.800000, -1.000000,-0.400000,0.800000, -1.000000,0.000000,2.400000,
        -0.700000,-0.400000,0.800000, -0.700000,0.400000,0.800000, -1.000000,0.400000,0.800000,
        -0.700000,-0.400000,0.800000, -0.700000,0.000000,2.400000, -0.700000,0.400000,0.800000,
        -1.000000,0.000000,-3.200000, -1.000000,0.300000,-3.100000, 0.500000,0.300000,-3.100000,
        -1.000000,-0.100000,-3.100000, -1.000000,0.000000,-3.200000, 0.500000,0.000000,-3.200000,
        0.500000,0.000000,3.200000, -1.000000,0.000000,3.200000, -1.000000,-0.100000,3.100000,
        0.500000,0.300000,3.100000, -1.000000,0.300000,3.100000, -1.000000,0.000000,3.200000,
        0.800000,0.000000,-3.100000, 0.500000,-0.100000,-3.100000, 0.500000,0.000000,-3.200000,
        -1.000000,0.000000,-3.000000, -1.000000,-0.100000,-3.100000, 0.500000,-0.100000,-3.100000,
        0.500000,0.000000,3.000000, -1.000000,0.000000,3.000000, -1.000000,0.300000,3.100000,
        -1.000000,0.300000,-3.100000, -1.000000,0.000000,-3.000000, 0.500000,0.000000,-3.000000,
        0.500000,0.000000,-3.000000, 0.800000,0.000000,-3.100000, 0.500000,0.300000,-3.100000,
        -1.000000,0.300000,-3.100000, -1.000000,0.000000,-3.200000, -1.000000,-0.100000,-3.100000,
        0.800000,0.000000,-3.100000, 0.500000,0.000000,-3.200000, 0.500000,0.300000,-3.100000,
        0.800000,0.000000,-3.100000, 0.500000,0.000000,-3.000000, 0.500000,-0.100000,-3.100000,
        0.500000,-0.100000,3.100000, -1.000000,-0.100000,3.100000, -1.000000,0.000000,3.000000,
        -1.000000,-0.100000,3.100000, -1.000000,0.000000,3.200000, -1.000000,0.300000,3.100000,
        0.800000,0.000000,3.100000, 0.500000,0.000000,3.200000, 0.500000,-0.100000,3.100000,
        0.800000,0.000000,3.100000, 0.500000,0.300000,3.100000, 0.500000,0.000000,3.200000,
        0.800000,0.000000,3.100000, 0.500000,0.000000,3.000000, 0.500000,0.300000,3.100000,
        0.800000,0.000000,3.100000, 0.500000,-0.100000,3.100000, 0.500000,0.000000,3.000000,
        0.999999,0.700000,1.000001, 3.000000,0.000000,1.000001, 1.999999,0.600000,0.700001,
        3.000000,0.000000,-0.999999, 3.000000,0.000000,1.000001, 1.000000,-0.500000,1.000000,
        0.500000,0.000000,-3.000000, 3.000000,0.000000,-0.999999, 1.000000,-0.500000,-1.000000,
        1.000000,-0.500000,-1.000000, 1.000000,-0.500000,1.000000, -1.000000,-0.500000,-1.000000,
        1.000000,0.700000,-0.999999, -1.000000,0.500000,-1.000000, 0.999999,0.700000,1.000001,
        0.500000,0.000000,3.000000, 0.999999,0.700000,1.000001, -1.000000,0.000000,3.000000,
        0.500000,0.000000,-3.000000, 1.000000,-0.500000,-1.000000, -1.000000,0.000000,-3.000000,
        -1.000000,-0.500000,1.000000, 1.000000,-0.500000,1.000000, -1.000000,0.000000,3.000000,
        -1.000000,0.500000,-1.000000, 1.000000,0.700000,-0.999999, -1.000000,0.000000,-3.000000,
        3.000000,0.000000,1.000001, 3.000000,0.000000,-0.999999, 1.999999,0.600000,0.700001,
        1.000000,0.700000,-0.999999, 0.999999,0.700000,1.000001, 2.000000,0.600000,-0.699999,
        -1.000000,0.000000,2.400000, -1.000000,0.000000,3.000000, -1.000000,0.400000,0.800000,
        -1.000000,-0.400000,0.800000, -1.000000,0.400000,0.800000, -1.000000,-0.400000,-0.800000,
        -1.000000,-0.400000,0.800000, -1.000000,-0.400000,-0.800000, -1.000000,-0.500000,1.000000,
        -1.000000,0.000000,-2.400000, -1.000000,0.000000,-3.000000, -1.000000,-0.400000,-0.800000,
        -1.000000,0.500000,1.000000, -1.000000,0.500000,-1.000000, -1.000000,0.400000,0.800000,
        -1.000000,0.000000,2.400000, -1.000000,-0.400000,0.800000, -1.000000,0.000000,3.000000,
        -1.000000,0.000000,-2.400000, -1.000000,0.400000,-0.800000, -1.000000,0.000000,-3.000000,
        -0.700000,0.400000,-0.800000, -0.700000,-0.400000,-0.800000, -1.000000,0.400000,-0.800000,
        -0.700000,0.000000,-2.400000, -0.700000,0.400000,-0.800000, -1.000000,0.000000,-2.400000,
        -0.700000,0.000000,-2.400000, -1.000000,0.000000,-2.400000, -0.700000,-0.400000,-0.800000,
        -0.700000,0.000000,2.400000, -1.000000,0.000000,2.400000, -0.700000,0.400000,0.800000,
        -0.700000,0.000000,2.400000, -0.700000,-0.400000,0.800000, -1.000000,0.000000,2.400000,
        -1.000000,-0.400000,0.800000, -0.700000,-0.400000,0.800000, -1.000000,0.400000,0.800000,
        0.500000,0.000000,-3.200000, -1.000000,0.000000,-3.200000, 0.500000,0.300000,-3.100000,
        0.500000,-0.100000,-3.100000, -1.000000,-0.100000,-3.100000, 0.500000,0.000000,-3.200000,
        0.500000,-0.100000,3.100000, 0.500000,0.000000,3.200000, -1.000000,-0.100000,3.100000,
        0.500000,0.000000,3.200000, 0.500000,0.300000,3.100000, -1.000000,0.000000,3.200000,
        0.500000,0.000000,-3.000000, -1.000000,0.000000,-3.000000, 0.500000,-0.100000,-3.100000,
        0.500000,0.300000,3.100000, 0.500000,0.000000,3.000000, -1.000000,0.300000,3.100000,
        0.500000,0.300000,-3.100000, -1.000000,0.300000,-3.100000, 0.500000,0.000000,-3.000000,
        -1.000000,0.000000,-3.000000, -1.000000,0.300000,-3.100000, -1.000000,-0.100000,-3.100000,
        0.500000,0.000000,3.000000, 0.500000,-0.100000,3.100000, -1.000000,0.000000,3.000000,
        -1.000000,0.000000,3.000000, -1.000000,-0.100000,3.100000, -1.000000,0.300000,3.100000,
        1.000000,-0.500000,-1.000000, 3.000000,0.000000,-0.999999, 1.000000,-0.500000,1.000000
    };

    float coordTextureTmp[] = {
        0.454381,0.781965, 0.454381,0.595359, 0.640988,0.595359,
        0.452763,0.185726, 0.642743,0.185726, 0.642744,0.375707,
        0.452763,0.565688, 0.452763,0.375707, 0.481260,0.470698,
        0.642744,0.375707, 0.642743,0.185726, 0.832724,0.185726,
        0.640988,0.781965, 0.640988,0.595359, 0.827594,0.595359,
        0.454381,0.781965, 0.267774,0.735314, 0.267774,0.595359,
        0.452763,0.375707, 0.262782,0.328212, 0.262782,0.185726,
        0.452763,0.565688, 0.481260,0.470698, 0.614246,0.470697,
        0.452763,0.565688, 0.262782,0.328212, 0.452763,0.375707,
        0.642744,0.375707, 0.614246,0.470697, 0.481260,0.470698,
        0.832724,0.328212, 0.642744,0.565688, 0.642744,0.375707,
        0.454381,0.968572, 0.267774,0.735314, 0.454381,0.781965,
        0.266793,0.095536, 0.460359,0.047145, 0.479715,0.056823,
        0.479715,0.056823, 0.634567,0.056823, 0.634567,0.134249,
        0.634567,0.134249, 0.653924,0.143928, 0.460358,0.143928,
        0.847489,0.095536, 0.653924,0.143928, 0.634567,0.134249,
        0.653924,0.047145, 0.634567,0.056823, 0.479715,0.056823,
        0.479715,0.134249, 0.460358,0.143928, 0.266793,0.095536,
        0.634567,0.056823, 0.653924,0.047145, 0.847489,0.095536,
        0.789420,0.095536, 0.634567,0.134249, 0.634567,0.056823,
        0.216525,0.098396, 0.239695,0.098467, 0.239505,0.160253,
        0.169238,0.160111, 0.146069,0.160182, 0.145690,0.036610,
        0.192408,0.036539, 0.192787,0.160110, 0.169618,0.160182,
        0.193166,0.160182, 0.192787,0.036610, 0.215957,0.036539,
        0.145311,0.160182, 0.122141,0.160110, 0.122520,0.036539,
        0.216525,0.098396, 0.216336,0.036610, 0.239505,0.036539,
        0.479715,0.134249, 0.324863,0.095536, 0.479715,0.056823,
        0.205008,0.456626, 0.185588,0.452171, 0.185290,0.247637,
        0.224422,0.456598, 0.205008,0.456626, 0.204710,0.252093,
        0.175364,0.688978, 0.175639,0.485477, 0.184317,0.488137,
        0.131954,0.688919, 0.132229,0.485418, 0.175639,0.485477,
        0.214356,0.210051, 0.224124,0.252065, 0.204710,0.252093,
        0.176612,0.210110, 0.185290,0.212770, 0.185015,0.416272,
        0.203737,0.527460, 0.204035,0.731993, 0.184615,0.727538,
        0.133202,0.210051, 0.176612,0.210110, 0.176337,0.413611,
        0.176337,0.413611, 0.171938,0.456292, 0.132927,0.413553,
        0.224422,0.262136, 0.224439,0.218726, 0.241806,0.210051,
        0.214356,0.210051, 0.204710,0.252093, 0.185290,0.247637,
        0.171938,0.456292, 0.176337,0.413611, 0.185015,0.416272,
        0.223151,0.527431, 0.223449,0.731965, 0.204035,0.731993,
        0.232124,0.485418, 0.249491,0.494093, 0.249508,0.537503,
        0.170965,0.731659, 0.175364,0.688978, 0.184042,0.691638,
        0.170965,0.731659, 0.131954,0.688919, 0.175364,0.688978,
        0.213383,0.485418, 0.203737,0.527460, 0.184317,0.523004,
        0.213383,0.485418, 0.223151,0.527431, 0.203737,0.527460,
        0.642744,0.375707, 0.642744,0.565688, 0.614246,0.470697,
        0.640988,0.968572, 0.454381,0.968572, 0.454381,0.781965,
        0.827594,0.735314, 0.640988,0.968572, 0.640988,0.781965,
        0.640988,0.781965, 0.454381,0.781965, 0.640988,0.595359,
        0.452763,0.375707, 0.452763,0.185726, 0.642744,0.375707,
        0.832724,0.328212, 0.642744,0.375707, 0.832724,0.185726,
        0.827594,0.735314, 0.640988,0.781965, 0.827594,0.595359,
        0.454381,0.595359, 0.454381,0.781965, 0.267774,0.595359,
        0.452763,0.185726, 0.452763,0.375707, 0.262782,0.185726,
        0.642744,0.565688, 0.452763,0.565688, 0.614246,0.470697,
        0.452763,0.375707, 0.642744,0.375707, 0.481260,0.470698,
        0.324863,0.095536, 0.266793,0.095536, 0.479715,0.056823,
        0.479715,0.134249, 0.479715,0.056823, 0.634567,0.134249,
        0.479715,0.134249, 0.634567,0.134249, 0.460358,0.143928,
        0.789420,0.095536, 0.847489,0.095536, 0.634567,0.134249,
        0.460359,0.047145, 0.653924,0.047145, 0.479715,0.056823,
        0.324863,0.095536, 0.479715,0.134249, 0.266793,0.095536,
        0.789420,0.095536, 0.634567,0.056823, 0.847489,0.095536,
        0.216336,0.160182, 0.216525,0.098396, 0.239505,0.160253,
        0.168859,0.036539, 0.169238,0.160111, 0.145690,0.036610,
        0.169238,0.036610, 0.192408,0.036539, 0.169618,0.160182,
        0.216336,0.160110, 0.193166,0.160182, 0.215957,0.036539,
        0.145690,0.036610, 0.145311,0.160182, 0.122520,0.036539,
        0.239695,0.098325, 0.216525,0.098396, 0.239505,0.036539,
        0.204710,0.252093, 0.205008,0.456626, 0.185290,0.247637,
        0.224124,0.252065, 0.224422,0.456598, 0.204710,0.252093,
        0.184042,0.691638, 0.175364,0.688978, 0.184317,0.488137,
        0.175364,0.688978, 0.131954,0.688919, 0.175639,0.485477,
        0.176337,0.413611, 0.176612,0.210110, 0.185015,0.416272,
        0.184317,0.523004, 0.203737,0.527460, 0.184615,0.727538,
        0.132927,0.413553, 0.133202,0.210051, 0.176337,0.413611,
        0.250481,0.227418, 0.224422,0.262136, 0.241806,0.210051,
        0.203737,0.527460, 0.223151,0.527431, 0.204035,0.731993,
        0.223449,0.502785, 0.232124,0.485418, 0.249508,0.537503,
        0.640988,0.781965, 0.640988,0.968572, 0.454381,0.781965
    };

    float normalsTmp[] = {
        0.000000,-1.000000,0.000000, 0.000000,-1.000000,0.000000, 0.000000,-1.000000,0.000000,
        -0.099500,0.995000,-0.000000, -0.099500,0.995000,-0.000000, -0.099500,0.995000,-0.000000,
        0.259700,0.741900,-0.618200, 0.259700,0.741900,-0.618200, 0.259700,0.741900,-0.618200,
        -0.096600,0.965600,0.241400, -0.096600,0.965600,0.241400, -0.096600,0.965600,0.241400,
        0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500,
        -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500,
        0.000000,0.943900,-0.330400, 0.000000,0.943900,-0.330400, 0.000000,0.943900,-0.330400,
        0.514500,0.857500,0.000000, 0.514500,0.857500,0.000000, 0.514500,0.857500,0.000000,
        0.305300,0.872400,-0.381700, 0.305300,0.872400,-0.381700, 0.305300,0.872400,-0.381700,
        0.099500,0.995000,0.000000, 0.099500,0.995000,0.000000, 0.099500,0.995000,0.000000,
        0.305300,0.872400,0.381700, 0.305300,0.872400,0.381700, 0.305300,0.872400,0.381700,
        0.232100,-0.928400,0.290100, 0.232100,-0.928400,0.290100, 0.232100,-0.928400,0.290100,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.000000,0.000000,-1.000000, 0.000000,0.000000,-1.000000, 0.000000,0.000000,-1.000000,
        -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500,
        -0.000000,0.970100,0.242500, -0.000000,0.970100,0.242500, -0.000000,0.970100,0.242500,
        0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500,
        0.000000,0.970100,-0.242500, 0.000000,0.970100,-0.242500, 0.000000,0.970100,-0.242500,
        -0.000000,0.000000,1.000000, -0.000000,0.000000,1.000000, -0.000000,0.000000,1.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700,
        0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100,
        -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100,
        -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700,
        0.229400,-0.688200,-0.688200, 0.229400,-0.688200,-0.688200, 0.229400,-0.688200,-0.688200,
        -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100,
        0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700,
        -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700,
        0.301500,0.301500,0.904500, 0.301500,0.301500,0.904500, 0.301500,0.301500,0.904500,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.301500,0.301500,-0.904500, 0.301500,0.301500,-0.904500, 0.301500,0.301500,-0.904500,
        0.229400,-0.688200,0.688200, 0.229400,-0.688200,0.688200, 0.229400,-0.688200,0.688200,
        0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.229400,-0.688200,0.688200, 0.229400,-0.688200,0.688200, 0.229400,-0.688200,0.688200,
        0.301500,0.301500,0.904500, 0.301500,0.301500,0.904500, 0.301500,0.301500,0.904500,
        0.301500,0.301500,-0.904500, 0.301500,0.301500,-0.904500, 0.301500,0.301500,-0.904500,
        0.229400,-0.688200,-0.688200, 0.229400,-0.688200,-0.688200, 0.229400,-0.688200,-0.688200,
        0.259700,0.741900,0.618200, 0.259700,0.741900,0.618200, 0.259700,0.741900,0.618200,
        0.242500,-0.970100,0.000000, 0.242500,-0.970100,0.000000, 0.242500,-0.970100,0.000000,
        0.232100,-0.928400,-0.290100, 0.232100,-0.928400,-0.290100, 0.232100,-0.928400,-0.290100,
        0.000000,-1.000000,0.000000, 0.000000,-1.000000,0.000000, 0.000000,-1.000000,0.000000,
        -0.099500,0.995000,-0.000000, -0.099500,0.995000,-0.000000, -0.099500,0.995000,-0.000000,
        -0.000000,0.943900,0.330400, -0.000000,0.943900,0.330400, -0.000000,0.943900,0.330400,
        0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500,
        -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500,
        -0.096600,0.965600,-0.241400, -0.096600,0.965600,-0.241400, -0.096600,0.965600,-0.241400,
        0.514500,0.857500,0.000000, 0.514500,0.857500,0.000000, 0.514500,0.857500,0.000000,
        0.099500,0.995000,0.000000, 0.099500,0.995000,0.000000, 0.099500,0.995000,0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.000000,0.000000,-1.000000, 0.000000,0.000000,-1.000000, 0.000000,0.000000,-1.000000,
        -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500, -0.000000,-0.970100,0.242500,
        -0.000000,0.970100,0.242500, -0.000000,0.970100,0.242500, -0.000000,0.970100,0.242500,
        0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500, 0.000000,-0.970100,-0.242500,
        0.000000,0.970100,-0.242500, 0.000000,0.970100,-0.242500, 0.000000,0.970100,-0.242500,
        -0.000000,0.000000,1.000000, -0.000000,0.000000,1.000000, -0.000000,0.000000,1.000000,
        0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700,
        0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100,
        -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100,
        -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700,
        -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100, -0.000000,-0.707100,0.707100,
        0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700, 0.000000,0.316200,-0.948700,
        -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700, -0.000000,0.316200,0.948700,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100, 0.000000,-0.707100,-0.707100,
        -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000, -1.000000,0.000000,-0.000000,
        0.242500,-0.970100,0.000000, 0.242500,-0.970100,0.000000, 0.242500,-0.970100,0.000000
    };

    for(int i(0); i<720; i++)
    {
        m_vertex[i] = vertexTmp[i];
        m_normals[i] = normalsTmp[i];
    }
    for(int i(0); i<480; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}

Ship::~Ship(){}

void Ship::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
        glEnableVertexAttribArray(2);

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindTexture(GL_TEXTURE_2D, m_texture.getID());
        glDrawArrays(GL_TRIANGLES, 0, 240);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    glUseProgram(0);
}
