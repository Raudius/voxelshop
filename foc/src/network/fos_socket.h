#ifndef FOS_SOCKET_H
#define FOS_SOCKET_H

#include "s3eSocket.h"
#include <boost\shared_ptr.hpp>

#include <network\fantasy_messages.pb.h>
using namespace com::pixelatedgames::fos::protobufs;

class fos_socket {
private:
	s3eSocket				*_socket;
	bool					_is_connected;
	s3eSocketError			_errors;
	static const int32		_read_buf_len = 1024;
	uint8					_read_buf[_read_buf_len];
	static const int32		_send_buf_len = 1024;
	uint8					_send_buf[_send_buf_len];
public:
	fos_socket();
	~fos_socket();

	void connect(std::string ip, uint16 port);
	void receive();
	void send(fantasy_message fm);

	bool is_connected() { return _is_connected; }
	s3eSocketError is_errors() { return _errors; } 

private:
	void connection_succeeded();
	void connection_failed();

	friend int32 connect_callback(s3eSocket *s, void *systemData, void *userData);
};

int32 connect_callback(s3eSocket *s, void *systemData, void *userData);

typedef boost::shared_ptr<fos_socket> shared_fos_socket;

#endif