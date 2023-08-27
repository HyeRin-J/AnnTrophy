#pragma once
#include "pch.h"

#include <iostream>
#include <deque>
#include <map>
#include <list>
#include <string>

#include "BaseMessage.h"
#include "CustomMessage.h"
#include "SingletonManager.h"
#include "MessageSystem.h"
#include "CustomClass.h"

using namespace std;

bool CustomClass::HandleYourMesssageListener(BaseMessage* msg)
{
    if (static_cast<CustomMessage*>(msg) == nullptr)
    {
       cout<<"HandleYourMesssageListener : Message is null!"<<endl;
        return false;
    }

    CustomMessage* castMsg = static_cast<CustomMessage*>(msg);
    if (castMsg == nullptr)
    {
        cout << "HandleYourMesssageListener : Cast Message is null!" << endl;
        return false;
    }

    cout << "HandleYourMesssageListener : Got the message!" << castMsg->m_Value << endl; // fucking event type


    return true;
}

void CustomClass::Awake()
{
    MessageSystem::GetInstance()->AttachListener(new CustomMessage("CustomMessage"), CustomClass::HandleYourMesssageListener);
}

void CustomClass::OnDestroy()
{
    MessageSystem::GetInstance()->DetachListener(new CustomMessage("CustomMessage"), CustomClass::HandleYourMesssageListener);
}
