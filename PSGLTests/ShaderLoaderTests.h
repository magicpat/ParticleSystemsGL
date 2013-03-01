//
//  ShaderLoaderTests.h
//  ParticleSystemsGL
//
//  Created by Patrick Stapfer on 09.02.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystemsGL__ShaderLoaderTests__
#define __ParticleSystemsGL__ShaderLoaderTests__

#include <iostream>
#include "gtest/gtest.h"
#include "ShaderLoader.h"

class ShaderLoaderTests : public testing::Test
{
protected:
    virtual void SetUp(){
        printf("bla1");
        printf("bla2");
        printf("bla3");
    }
    
    //virtual void TearDown(){}
private:
    ;
};




#endif /* defined(__ParticleSystemsGL__ShaderLoaderTests__) */
