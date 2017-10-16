/* <base/on_destroy.h>

   ----------------------------------------------------------------------------
   Copyright 2017 Dave Peterson <dave@dspeterson.com>

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

   Utility class for executing caller-supplied function on destructor
   invocation.
 */

#pragma once

#include <cassert>
#include <functional>

#include <base/no_copy_semantics.h>

namespace Base {

  class TOnDestroy final {
    NO_COPY_SEMANTICS(TOnDestroy);

    public:
    TOnDestroy(const std::function<void() noexcept> &action)
        : Action(action),
          Active(true) {
    }

    ~TOnDestroy() noexcept {
      if (Active) {
        Action();
      }
    }

    void Cancel() noexcept {
      assert(this);
      Active = false;
    }

    private:
    const std::function<void() noexcept> Action;

    bool Active;
  };  // TOnDestroy

}  // Base
