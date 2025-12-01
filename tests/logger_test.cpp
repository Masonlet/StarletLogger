#include <gtest/gtest.h>

#include "starlet-logger/logger.hpp"

#include <vector>

namespace SLogger = Starlet::Logger;

inline void expectStderrContains(const std::vector<std::string>& expectedSubstrings) {
	std::string output = testing::internal::GetCapturedStderr();
	for (const std::string& substring : expectedSubstrings)
		EXPECT_NE(output.find(substring), std::string::npos) << "Expected to find: \"" << substring << "\" in stderr output";
}

inline void expectStdoutContains(const std::vector<std::string>& expectedSubstrings) {
	std::string output = testing::internal::GetCapturedStdout();
	for (const std::string& substring : expectedSubstrings)
		EXPECT_NE(output.find(substring), std::string::npos) << "Expected to find: \"" << substring << "\" in stdout output";
}

TEST(LoggerTest, BasicLog) {
	testing::internal::CaptureStdout();
	SLogger::log("TestCaller", "TestFunction", "Test message");
	expectStdoutContains({ "[TestCaller TestFunction INFO] Test message\n" });
}
#ifndef NDEBUG
TEST(LoggerTest, BasicDebugLog) {
	testing::internal::CaptureStdout();
	SLogger::debug("TestCaller", "TestFunction", "True message");
	expectStdoutContains({ "[TestCaller TestFunction DEBUG] True message\n" });
}
#endif
TEST(LoggerTest, BasicWarningLog) {
	testing::internal::CaptureStderr();
	SLogger::warning("TestCaller", "TestFunction", "Test message");
	expectStderrContains({ "[TestCaller TestFunction WARNING] Test message\n" });
}
TEST(LoggerTest, BasicErrorLog) {
	testing::internal::CaptureStderr();
	SLogger::error("TestCaller", "TestFunction", "Test message");
	expectStderrContains({ "[TestCaller TestFunction ERROR] Test message\n" });
}

TEST(LoggerTest, AllLevels) {
	testing::internal::CaptureStdout();
	SLogger::log("Caller", "Func", "info");
	SLogger::debug("Caller", "Func", "debug");
	SLogger::warning("Caller", "Func", "warning", true);
	expectStdoutContains({
		"[Caller Func INFO] info\n",
		"[Caller Func WARNING] warning\n"
	#ifndef NDEBUG
		, "[Caller Func DEBUG] debug\n"
	#endif
	});

	testing::internal::CaptureStderr();
	SLogger::error("Caller", "Func", "error");
	SLogger::warning("Caller", "Func", "warning");
	expectStderrContains({
		"[Caller Func ERROR] error\n",
		"[Caller Func WARNING] warning\n"
	});
}

TEST(LoggerTest, AllErrorLevels) {
	testing::internal::CaptureStderr();
	SLogger::error("Caller", "Func", "error");
	expectStderrContains({ "[Caller Func ERROR] error\n" });
}

TEST(LoggerTest, WarningLogReturnValue) {
	testing::internal::CaptureStdout();
	EXPECT_TRUE(SLogger::warning("C", "F", "msg", true));
	expectStdoutContains({ "[C F WARNING] msg\n" });

	testing::internal::CaptureStderr();
	EXPECT_FALSE(SLogger::warning("C", "F", "msg", false));
	expectStderrContains({ "[C F WARNING] msg\n" });
}

TEST(LoggerTest, ErrorReturnsFalse) {
	testing::internal::CaptureStderr();
	EXPECT_FALSE(SLogger::error("C", "F", "msg"));
	expectStderrContains({ "[C F ERROR] msg\n" });
}