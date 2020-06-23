//
//  IGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 25/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef IGenerator_h
#define IGenerator_h

template <class T>
class IGenerator
{
public:
    virtual ~IGenerator() {}
    IGenerator() {}
    IGenerator(const IGenerator&) = delete;
    IGenerator& operator=(const IGenerator&) = delete;
    IGenerator(IGenerator&&) = default;
    IGenerator& operator=(IGenerator&&) = default;

public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual T currentItem() const = 0;
};

#endif /* IGenerator_h */
