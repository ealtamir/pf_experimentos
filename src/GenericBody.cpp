#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"
#include "GenericActuator.h"
#include "MetaActuator.h"


GenericBody::GenericBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 18 * 8;
}

void GenericBody::setActuatorValues(std::vector<double> vals) {
    Actuator* actuator;
    double values[144] = {
        // First step
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5],
        vals[6], vals[7], vals[8], vals[9], vals[10], vals[11],
        vals[12], vals[13], vals[14], vals[15], vals[16], vals[17],
        
        vals[18], vals[19], vals[20], vals[21], vals[22], vals[23],
        vals[24], vals[25], vals[26], vals[27], vals[28], vals[29],
        vals[30], vals[31], vals[32], vals[33], vals[34], vals[35],
        
        vals[36], vals[37], vals[38], vals[39], vals[40], vals[41],
        vals[42], vals[43], vals[44], vals[45], vals[46], vals[47],
        vals[48], vals[49], vals[50], vals[51], vals[52], vals[53],
        
        vals[54], vals[55], vals[56], vals[57], vals[58], vals[59],
        vals[60], vals[61], vals[62], vals[63], vals[64], vals[65],
        vals[66], vals[67], vals[68], vals[69], vals[70], vals[71],
        
        vals[72], vals[73], vals[74], vals[75], vals[76], vals[77],
        vals[78], vals[79], vals[80], vals[81], vals[82], vals[83],
        vals[84], vals[85], vals[86], vals[87], vals[88], vals[89],
        // First step
        // Second step
        vals[90], vals[91], vals[92], vals[93], vals[94], vals[95],
        vals[96], vals[97], vals[98], vals[99], vals[100], vals[101],
        vals[102], vals[103], vals[104], vals[105], vals[106], vals[107],
        
        vals[108], vals[109], vals[110], vals[111], vals[112], vals[113],
        vals[114], vals[115], vals[116], vals[117], vals[118], vals[119],
        vals[120], vals[121], vals[122], vals[123], vals[124], vals[125],
        
        vals[126], vals[127], vals[128], vals[129], vals[130], vals[131],
        vals[132], vals[133], vals[134], vals[135], vals[136], vals[137],
        vals[138], vals[139], vals[140], vals[141], vals[142], vals[143],
        // Second step
    };
    
    //
    // Se le pasan al meta actuator
    //
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftLowerLeg->getActuator());
    actuator->setActuatorValues(values, &values[90]);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftUpperLeg->getActuator());
    actuator->setActuatorValues(&values[18], &values[108]);
    
    values[94] += SIMD_PI;
    values[112] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<Actuator*>(rightLowerLeg->getActuator());
    actuator->setActuatorValues(&values[36], &values[24]);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<Actuator*>(rightUpperLeg->getActuator());
    actuator->setActuatorValues(&values[54], &values[30]);
}