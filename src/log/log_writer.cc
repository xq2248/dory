/* <log/log_writer.cc>

   ----------------------------------------------------------------------------
   Copyright 2019 Dave Peterson <dave@dspeterson.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   ----------------------------------------------------------------------------

   Implements <log/log_writer.h>.
 */

#include <log/log_writer.h>

#include <mutex>

#include <log/combined_log_writer.h>

using namespace Base;
using namespace Log;

static std::shared_ptr<TCombinedLogWriter> LogWriter;

static std::mutex LogWriterMutex;

void Log::SetLogWriter(bool enable_stdout_stderr, bool enable_syslog,
    const std::string &file_path, const TOpt<mode_t> &file_mode) {
  std::lock_guard<std::mutex> lock(LogWriterMutex);
  LogWriter = !LogWriter ?
      std::make_shared<TCombinedLogWriter>(enable_stdout_stderr, enable_syslog,
          file_path, file_mode) :
      std::make_shared<TCombinedLogWriter>(*LogWriter, enable_stdout_stderr,
          enable_syslog, file_path, file_mode);
}

void Log::DropLogWriter() {
  std::lock_guard<std::mutex> lock(LogWriterMutex);
  LogWriter.reset();
}

bool Log::HandleLogfileReopenRequest() {
  std::lock_guard<std::mutex> lock(LogWriterMutex);

  if (!LogWriter || !LogWriter->FileLoggingIsEnabled()) {
    return false;
  }

  LogWriter = std::make_shared<TCombinedLogWriter>(
      LogWriter->StdoutStderrLoggingIsEnabled(),
      LogWriter->SyslogLoggingIsEnabled(), LogWriter->GetFilePath(),
      LogWriter->GetFileOpenMode());
  return true;
}

std::shared_ptr<TLogWriterBase> Log::GetLogWriter() noexcept {
  std::lock_guard<std::mutex> lock(LogWriterMutex);

  if (!LogWriter) {
    /* If no log writer has yet been created, make a default one that logs only
       to stdout/stderr. */
    LogWriter = std::make_shared<TCombinedLogWriter>(
        true /* enable_stdout_stderr */, false /* enable_syslog */,
        std::string() /* file_path */, TOpt<mode_t>() /* file_mode */);
  }

  return LogWriter;
}
