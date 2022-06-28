#pragma once
#ifndef MESSAGE
#define MESSAGE
class BaseMessage {
protected:
	unsigned char* messageBuffer;
	int messageId;
	int messageType;

public:
	BaseMessage(unsigned char* buffer, int id);
	BaseMessage(int type, int id);
	~BaseMessage();
	virtual void parseMessage() = 0;
	virtual void parseBack() = 0;
	virtual void print() = 0;
	unsigned char* getMessageBuffer();

};

class StatusMessage :public BaseMessage {
protected:
	short status;

public:
	StatusMessage(unsigned char* buffer, int id) ;
	StatusMessage(int id, short status) ;
	virtual void parseMessage();
	virtual void parseBack();
	virtual void print();
};

class DiscoverMessage :public BaseMessage {
protected:
	float distance;
	float angle;
	float speed;

public:
	DiscoverMessage(unsigned char* buffer, int id);
	DiscoverMessage(int id, float distance, float angle, float speed);
	virtual void parseMessage();
	virtual void parseBack();
	virtual void print();
};
#endif // !MESSAGE



