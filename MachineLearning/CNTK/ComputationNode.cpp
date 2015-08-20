//
// <copyright file="ComputationNode.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//

#define _CRT_SECURE_NO_WARNINGS // "secure" CRT not available on all platforms  --add this at the top of all CPP files that give "function or variable may be unsafe" warnings

#include "ComputationNode.h"
#include "InputAndParamNodes.h"

namespace Microsoft { namespace MSR { namespace CNTK {

    // code

    template<typename ElemType>
    /*virtual*/ void ComputationNode<ElemType>::MoveMatricesToDevice(const DEVICEID_TYPE deviceId)
    {
        if (deviceId != AUTOPLACEMATRIX)
        {
            m_functionValues.TransferToDeviceIfNotTherAndNotAutoPlace(deviceId, true, m_functionValues.HasNoElements());
            m_gradientValues.TransferToDeviceIfNotTherAndNotAutoPlace(deviceId, true, m_gradientValues.HasNoElements());
        }
    }

    template<typename ElemType>
    /*virtual*/ void ComputationNode<ElemType>::DumpNodeInfo(const bool /*printValues*/, File& fstream) const
    {
        fstream << L"\n" + NodeName() + L"=" + OperationName();

        if (!IsLeaf())
        {
            fstream << wstring(L"(");
            for (size_t i = 0; i<ChildrenSize(); i++)
            {
                if (i > 0)
                    fstream << wstring(L",");
                fstream << (Inputs(i) ? Inputs(i)->NodeName() : L"NULL");
            }
            fstream << wstring(L")");
        }
    }


    // instantiate the core class templates

    typedef Matrix<float> FloatMatrix;
    typedef Matrix<double> DoubleMatrix;

    template<> atomic_ullong ComputationNode<float>::s_timeStampCounter = ATOMIC_VAR_INIT(0);
    template<> atomic_ullong ComputationNode<double>::s_timeStampCounter = ATOMIC_VAR_INIT(0);

    template<> std::map<size_t, std::map<size_t, FloatMatrix*>> ComputationNode<float>::s_constOnes{};
    template<> std::map<size_t, std::map<size_t, DoubleMatrix*>> ComputationNode<double>::s_constOnes{};

    template class LearnableParameter<float>;
    template class LearnableParameter<double>;
}}}
