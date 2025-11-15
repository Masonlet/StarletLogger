#include <gtest/gtest.h>
#include "starlet-logger/logger.hpp"

namespace SLogger = Starlet::Logger;

TEST(LoggerTest, BasicLog) {
	testing::internal::CaptureStdout();
	SLogger::log("TestCaller", "TestFunction", "Test message");
	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "[TestCaller TestFunction INFO] Test message\n");
}
TEST(LoggerTest, BasicDebugLog) {
	testing::internal::CaptureStdout();
	SLogger::debug("TestCaller", "TestFunction", "True message");
	const std::string outputT = testing::internal::GetCapturedStdout();
	EXPECT_EQ(outputT, "[TestCaller TestFunction DEBUG] True message\n");
}
TEST(LoggerTest, BasicWarningLog) {
	testing::internal::CaptureStderr();
	SLogger::warning("TestCaller", "TestFunction", "Test message");
	const std::string output = testing::internal::GetCapturedStderr();
	EXPECT_EQ(output, "[TestCaller TestFunction WARNING] Test message\n");
}
TEST(LoggerTest, BasicErrorLog) {
	testing::internal::CaptureStderr();
	SLogger::error("TestCaller", "TestFunction", "Test message");
	const std::string output = testing::internal::GetCapturedStderr();
	EXPECT_EQ(output, "[TestCaller TestFunction ERROR] Test message\n");
}

TEST(LoggerTest, AllLevels) {
	testing::internal::CaptureStdout();
	SLogger::log("Caller", "Func", "info");
	SLogger::debug("Caller", "Func", "debug");
	SLogger::warning("Caller", "Func", "warning", true);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("[Caller Func INFO] info\n"), std::string::npos);
	EXPECT_NE(output.find("[Caller Func DEBUG] debug\n"), std::string::npos);
	EXPECT_NE(output.find("[Caller Func WARNING] warning\n"), std::string::npos);

	testing::internal::CaptureStderr();
	SLogger::error("Caller", "Func", "error");
	SLogger::warning("Caller", "Func", "warning");
	output = testing::internal::GetCapturedStderr();
	EXPECT_NE(output.find("[Caller Func ERROR] error\n"), std::string::npos);
	EXPECT_NE(output.find("[Caller Func WARNING] warning\n"), std::string::npos);
}

TEST(LoggerTest, AllErrorLevels) {
	testing::internal::CaptureStderr();
	SLogger::error("Caller", "Func", "error");
	const std::string output = testing::internal::GetCapturedStderr();
	EXPECT_NE(output.find("[Caller Func ERROR] error\n"), std::string::npos);
}

TEST(LoggerTest, WarningLogReturnValue) {
	testing::internal::CaptureStdout();
	EXPECT_TRUE(SLogger::warning("C", "F", "msg", true));
	testing::internal::GetCapturedStdout();

	testing::internal::CaptureStderr();
	EXPECT_FALSE(SLogger::warning("C", "F", "msg", false));
	testing::internal::GetCapturedStderr();
}

TEST(LoggerTest, ErrorReturnsFalse) {
	testing::internal::CaptureStderr();
	EXPECT_FALSE(SLogger::error("C", "F", "msg"));
	testing::internal::GetCapturedStderr();
}