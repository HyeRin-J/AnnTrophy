#pragma once

class CustomMessage : public BaseMessage
{
public:
	CustomMessage() { m_Name = "CustomMessage"; };
	CustomMessage(std::string name) { m_Name = name; };
};

