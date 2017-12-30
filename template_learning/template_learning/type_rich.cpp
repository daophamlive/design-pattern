//
//  type_rich.cpp
//  template_learning
//
//  Created by dao on 12/9/17.
//  Copyright © 2017 dao. All rights reserved.
//

#include <stdio.h>
#include "type_rich.h"
using Momentum = Value<MksUnit<1, 1, -1>>;
using DimensionlessQuantity = Value<MksUnit<0, 0, 0>>;
using Length = Value<MksUnit<1, 0, 0>>;
using Area = Value<MksUnit<2, 0, 0>>;
using Volume = Value<MksUnit<3, 0, 0>>;
using Mass = Value<MksUnit<0, 1, 0>>;
using Time = Value<MksUnit<0, 0, 1>>;
using Speed = Value<MksUnit<1, 0, -1>>;
using Acceleration = Value<MksUnit<1, 0, -2>>;
using Frequency = Value<MksUnit<0, 0, -1>>;
using Force = Value<MksUnit<1, 1, -2>>;
using Pressure = Value<MksUnit<-1, 1, -2>>;


class SpacecraftTrajectoryControl { public:
    void applyMomentumToSpacecraftBody(const Momentum& impulseValue)
    {}
};

void using_type_rich()
{
    SpacecraftTrajectoryControl control;

    //Force force { 13.75 };
    //control.applyMomentumToSpacecraftBody(force); // Compile-time error!
    
    Momentum momentum { 13.75 };
    control.applyMomentumToSpacecraftBody(momentum); // Compile-time OK!
    
}
