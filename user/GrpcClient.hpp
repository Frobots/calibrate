#ifndef GRPC_CLIENT_H__
#define GRPC_CLIENT_H__

#include <iostream>
#include <fstream>
#include <string>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include "Grpc.grpc.pb.h"
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <opencv2/opencv.hpp>
#include <memory.h>
#include <stdio.h>
using grpc::Status;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientWriter;
using namespace example;
using grpc::ClientContext;
#define GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH(INT_MAX)
class GrpcClient {
 public:
	//构造函数，创建一个频道，用于指向服务器
	GrpcClient(std::shared_ptr<Channel>channl):stu_(FormatData::NewStub(channl)) {}
	cv::Mat TargetDetect(cv::Mat img,std::vector<std::string> &class_name, std::vector<cv::Point2f> &rbox_centers, std::vector<float> &angles, std::vector<float> &scores);
 private:
	//这个是远程方法（API）的一个指针
	std::unique_ptr<FormatData::Stub> stu_;
}; // GrpcClient
#endif