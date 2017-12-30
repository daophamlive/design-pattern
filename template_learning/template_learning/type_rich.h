//
//  type_rich.h
//  template_learning
//
//  Created by dao on 12/9/17.
//  Copyright © 2017 dao. All rights reserved.
//

#ifndef type_rich_h
#define type_rich_h
template <int M, int K, int S>
struct MksUnit
{
    enum { metre = M, kilogram = K, second = S};
};

template <typename MksUnit>
class Value {
private:
    long double magnitude{ 0.0 };
public:
    explicit Value(const long double magnitude) : magnitude(magnitude)
    {}
    
    long double getMagnitude() const
    {
        return magnitude;
    }
};


#endif /* type_rich_h */
