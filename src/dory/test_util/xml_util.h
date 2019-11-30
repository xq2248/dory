/* <dory/test_util/xml_util.h>

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

   XML-related utility functions for testing.
 */

#pragma once

#include <string>

#include <dory/conf/conf.h>

namespace Dory {

  namespace TestUtil {

    /* Be sure to initialize Xerces XML processing library before calling this.
       See <dory/util/dory_xml_init.h>. */
    Conf::TConf XmlToConf(const std::string &xml);

  }  // TestUtil

}  // Dory
