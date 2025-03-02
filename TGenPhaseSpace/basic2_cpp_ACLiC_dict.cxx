// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dImntdIcdIUsersdISatyamsPTiwaridIDesktopdIPhDdIUbuntusPPhDdIPhDdIMCdITGenPhaseSpacedIbasic2_cpp_ACLiC_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/mnt/c/Users/Satyam Tiwari/Desktop/PhD/Ubuntu PhD/PhD/MC/TGenPhaseSpace/./basic2.cpp"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_basic2_cpp_ACLiC_dict_Impl() {
    static const char* headers[] = {
"./basic2.cpp",
nullptr
    };
    static const char* includePaths[] = {
"/snap/root-framework/943/usr/local/include",
"/snap/root-framework/943/usr/local/etc/",
"/snap/root-framework/943/usr/local/etc//cling",
"/snap/root-framework/943/usr/local/etc//cling/plugins/include",
"/snap/root-framework/943/usr/local/include/",
"/snap/root-framework/943/usr/local/include",
"/snap/root-framework/943/usr/local/include/",
"/mnt/c/Users/Satyam Tiwari/Desktop/PhD/Ubuntu PhD/PhD/MC/TGenPhaseSpace/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "basic2_cpp_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "basic2_cpp_ACLiC_dict dictionary payload"

#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./basic2.cpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"basic", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("basic2_cpp_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_basic2_cpp_ACLiC_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_basic2_cpp_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_basic2_cpp_ACLiC_dict() {
  TriggerDictionaryInitialization_basic2_cpp_ACLiC_dict_Impl();
}
