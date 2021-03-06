
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "azure/core/http/http.hpp"
#include "azure/core/http/pipeline.hpp"
#include "azure/core/nullable.hpp"
#include "azure/core/response.hpp"
#include "azure/storage/common/crypt.hpp"
#include "azure/storage/common/json.hpp"
#include "azure/storage/common/storage_common.hpp"
#include "azure/storage/common/storage_exception.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace Azure { namespace Storage { namespace Files { namespace DataLake {

  namespace Details {
    constexpr static const char* c_DefaultServiceApiVersion = "2020-02-10";
    constexpr static const char* c_PathDnsSuffixDefault = "dfs.core.windows.net";
    constexpr static const char* c_QueryFileSystemResource = "resource";
    constexpr static const char* c_QueryTimeout = "timeout";
    constexpr static const char* c_QueryRecursiveOptional = "recursive";
    constexpr static const char* c_QueryRecursiveRequired = "recursive";
    constexpr static const char* c_QueryContinuationToken = "continuation";
    constexpr static const char* c_QueryPathSetAccessControlRecursiveMode = "mode";
    constexpr static const char* c_QueryForceFlag = "forceflag";
    constexpr static const char* c_QueryDirectory = "directory";
    constexpr static const char* c_QueryPrefix = "prefix";
    constexpr static const char* c_QueryMaxResults = "maxresults";
    constexpr static const char* c_QueryUpn = "upn";
    constexpr static const char* c_QueryPosition = "position";
    constexpr static const char* c_QueryRetainUncommittedData = "retainuncommitteddata";
    constexpr static const char* c_QueryClose = "close";
    constexpr static const char* c_QueryResource = "resource";
    constexpr static const char* c_QueryPathResourceType = "resource";
    constexpr static const char* c_QueryPathRenameMode = "mode";
    constexpr static const char* c_QueryPathGetPropertiesAction = "action";
    constexpr static const char* c_QueryAction = "action";
    constexpr static const char* c_QueryMaxRecords = "maxrecords";
    constexpr static const char* c_QueryComp = "comp";
    constexpr static const char* c_HeaderApiVersionParameter = "x-ms-version";
    constexpr static const char* c_HeaderClientRequestId = "x-ms-client-request-id";
    constexpr static const char* c_HeaderIfMatch = "if-match";
    constexpr static const char* c_HeaderIfModifiedSince = "if-modified-since";
    constexpr static const char* c_HeaderIfNoneMatch = "if-none-match";
    constexpr static const char* c_HeaderIfUnmodifiedSince = "if-unmodified-since";
    constexpr static const char* c_HeaderLeaseIdOptional = "x-ms-lease-id";
    constexpr static const char* c_HeaderLeaseIdRequired = "x-ms-lease-id";
    constexpr static const char* c_HeaderProposedLeaseIdOptional = "x-ms-proposed-lease-id";
    constexpr static const char* c_HeaderProperties = "x-ms-properties";
    constexpr static const char* c_HeaderSourceIfMatch = "x-ms-source-if-match";
    constexpr static const char* c_HeaderSourceIfModifiedSince = "x-ms-source-if-modified-since";
    constexpr static const char* c_HeaderSourceIfNoneMatch = "x-ms-source-if-none-match";
    constexpr static const char* c_HeaderSourceIfUnmodifiedSince
        = "x-ms-source-if-unmodified-since";
    constexpr static const char* c_HeaderSourceLeaseId = "x-ms-source-lease-id";
    constexpr static const char* c_HeaderCacheControl = "x-ms-cache-control";
    constexpr static const char* c_HeaderContentDisposition = "x-ms-content-disposition";
    constexpr static const char* c_HeaderContentEncoding = "x-ms-content-encoding";
    constexpr static const char* c_HeaderContentLanguage = "x-ms-content-language";
    constexpr static const char* c_HeaderContentType = "x-ms-content-type";
    constexpr static const char* c_HeaderTransactionalContentMd5 = "content-md5";
    constexpr static const char* c_HeaderContentMd5 = "x-ms-content-md5";
    constexpr static const char* c_HeaderContentCrc64 = "x-ms-content-crc64";
    constexpr static const char* c_HeaderUmask = "x-ms-umask";
    constexpr static const char* c_HeaderPermissions = "x-ms-permissions";
    constexpr static const char* c_HeaderRenameSource = "x-ms-rename-source";
    constexpr static const char* c_HeaderOwner = "x-ms-owner";
    constexpr static const char* c_HeaderGroup = "x-ms-group";
    constexpr static const char* c_HeaderAcl = "x-ms-acl";
    constexpr static const char* c_HeaderContentLength = "content-length";
    constexpr static const char* c_HeaderPathExpiryOptions = "x-ms-expiry-option";
    constexpr static const char* c_HeaderPathExpiryTime = "x-ms-expiry-time";
    constexpr static const char* c_HeaderDate = "date";
    constexpr static const char* c_HeaderXMsRequestId = "x-ms-request-id";
    constexpr static const char* c_HeaderXMsClientRequestId = "x-ms-client-request-id";
    constexpr static const char* c_HeaderXMsVersion = "x-ms-version";
    constexpr static const char* c_HeaderXMsContinuation = "x-ms-continuation";
    constexpr static const char* c_HeaderXMsErrorCode = "x-ms-error-code";
    constexpr static const char* c_HeaderETag = "etag";
    constexpr static const char* c_HeaderLastModified = "last-modified";
    constexpr static const char* c_HeaderXMsNamespaceEnabled = "x-ms-namespace-enabled";
    constexpr static const char* c_HeaderXMsProperties = "x-ms-properties";
    constexpr static const char* c_HeaderPathLeaseAction = "x-ms-lease-action";
    constexpr static const char* c_HeaderXMsLeaseDuration = "x-ms-lease-duration";
    constexpr static const char* c_HeaderXMsLeaseBreakPeriod = "x-ms-lease-break-period";
    constexpr static const char* c_HeaderXMsLeaseId = "x-ms-lease-id";
    constexpr static const char* c_HeaderXMsLeaseTime = "x-ms-lease-time";
    constexpr static const char* c_HeaderRange = "range";
    constexpr static const char* c_HeaderXMsRangeGetContentMd5 = "x-ms-range-get-content-md5";
    constexpr static const char* c_HeaderAcceptRanges = "accept-ranges";
    constexpr static const char* c_HeaderContentRange = "content-range";
    constexpr static const char* c_HeaderContentMD5 = "content-md5";
    constexpr static const char* c_HeaderXMsResourceType = "x-ms-resource-type";
    constexpr static const char* c_HeaderXMsLeaseState = "x-ms-lease-state";
    constexpr static const char* c_HeaderXMsLeaseStatus = "x-ms-lease-status";
    constexpr static const char* c_HeaderXMsContentMd5 = "x-ms-content-md5";
    constexpr static const char* c_HeaderXMsOwner = "x-ms-owner";
    constexpr static const char* c_HeaderXMsGroup = "x-ms-group";
    constexpr static const char* c_HeaderXMsPermissions = "x-ms-permissions";
    constexpr static const char* c_HeaderXMsAcl = "x-ms-acl";
    constexpr static const char* c_HeaderXMsContentCrc64 = "x-ms-content-crc64";
    constexpr static const char* c_HeaderXMsRequestServerEncrypted
        = "x-ms-request-server-encrypted";
  } // namespace Details
  struct DataLakeHttpHeaders
  {
    std::string CacheControl;
    std::string ContentDisposition;
    std::string ContentEncoding;
    std::string ContentLanguage;
    std::string ContentType;
  };
  // Mode "set" sets POSIX access control rights on files and directories, "modify" modifies one or
  // more POSIX access control rights  that pre-exist on files and directories, "remove" removes one
  // or more POSIX access control rights  that were present earlier on files and directories
  enum class PathSetAccessControlRecursiveMode
  {
    Set,
    Modify,
    Remove,
    Unknown
  };

  // Required. Indicates mode of the expiry time
  enum class PathExpiryOptions
  {
    NeverExpire,
    RelativeToCreation,
    RelativeToNow,
    Absolute,
    Unknown
  };

  struct AclFailedEntry
  {
    std::string Name;
    std::string Type;
    std::string ErrorMessage;
  };

  struct SetAccessControlRecursiveResponse
  {
    int32_t DirectoriesSuccessful = int32_t();
    int32_t FilesSuccessful = int32_t();
    int32_t FailureCount = int32_t();
    std::vector<AclFailedEntry> FailedEntries;
  };

  struct Path
  {
    std::string Name;
    bool IsDirectory = bool();
    std::string LastModified;
    std::string ETag;
    int64_t ContentLength = int64_t();
    std::string Owner;
    std::string Group;
    std::string Permissions;
  };

  struct PathList
  {
    std::vector<Path> Paths;
  };

  struct FileSystem
  {
    std::string Name;
    std::string LastModified;
    std::string ETag;
  };

  struct FileSystemList
  {
    std::vector<FileSystem> Filesystems;
  };

  struct StorageError
  {

    // The service error response object.
    struct Error
    {
      std::string Code; // The service error code.
      std::string Message; // The service error message.
    };

    Error Error; // The service error response object.
  };

  // Required only for Create File and Create Directory. The value must be "file" or "directory".
  enum class PathResourceType
  {
    Directory,
    File,
    Unknown
  };

  // Optional. Valid only when namespace is enabled. This parameter determines the behavior of the
  // rename operation. The value must be "legacy" or "posix", and the default value will be "posix".
  enum class PathRenameMode
  {
    Legacy,
    Posix,
    Unknown
  };

  // There are five lease actions: "acquire", "break", "change", "renew", and "release". Use
  // "acquire" and specify the "x-ms-proposed-lease-id" and "x-ms-lease-duration" to acquire a new
  // lease. Use "break" to break an existing lease. When a lease is broken, the lease break period
  // is allowed to elapse, during which time no lease operation except break and release can be
  // performed on the file. When a lease is successfully broken, the response indicates the interval
  // in seconds until a new lease can be acquired. Use "change" and specify the current lease ID in
  // "x-ms-lease-id" and the new lease ID in "x-ms-proposed-lease-id" to change the lease ID of an
  // active lease. Use "renew" and specify the "x-ms-lease-id" to renew an existing lease. Use
  // "release" and specify the "x-ms-lease-id" to release a lease.
  enum class PathLeaseAction
  {
    Acquire,
    Break,
    Change,
    Renew,
    Release,
    Unknown
  };

  // Lease state of the resource.
  enum class LeaseStateType
  {
    Available,
    Leased,
    Expired,
    Breaking,
    Broken,
    Unknown
  };

  // The lease status of the resource.
  enum class LeaseStatusType
  {
    Locked,
    Unlocked,
    Unknown
  };

  // Optional. If the value is "getStatus" only the system defined properties for the path are
  // returned. If the value is "getAccessControl" the access control list is returned in the
  // response headers (Hierarchical Namespace must be enabled for the account), otherwise the
  // properties are returned.
  enum class PathGetPropertiesAction
  {
    GetAccessControl,
    GetStatus,
    Unknown
  };

  struct ServiceListFileSystemsResult
  {
    Azure::Core::Nullable<std::string> ContinuationToken;
    std::vector<FileSystem> Filesystems;
  };

  struct FileSystemCreateResult
  {
    std::string ETag;
    std::string LastModified;
    std::string NamespaceEnabled;
  };

  struct FileSystemSetPropertiesResult
  {
    std::string ETag;
    std::string LastModified;
  };

  struct FileSystemGetPropertiesResult
  {
    std::string ETag;
    std::string LastModified;
    std::string Properties;
    std::string NamespaceEnabled;
  };

  struct FileSystemDeleteResult
  {
  };

  struct FileSystemListPathsResult
  {
    Azure::Core::Nullable<std::string> ContinuationToken;
    std::vector<Path> Paths;
  };

  struct PathCreateResult
  {
    Azure::Core::Nullable<std::string> ETag;
    Azure::Core::Nullable<std::string> LastModified;
    Azure::Core::Nullable<std::string> ContinuationToken;
    Azure::Core::Nullable<int64_t> ContentLength;
  };

  struct PathLeaseResult
  {
    std::string ETag;
    std::string LastModified;
    std::string LeaseId;
    std::string LeaseTime;
  };

  struct PathReadResult
  {
    std::unique_ptr<Azure::Core::Http::BodyStream> BodyStream;
    std::string AcceptRanges;
    DataLakeHttpHeaders HttpHeaders;
    int64_t ContentLength = int64_t();
    Azure::Core::Nullable<std::string> ContentRange;
    Azure::Core::Nullable<std::string> TransactionalMd5;
    std::string ETag;
    std::string LastModified;
    std::string ResourceType;
    Azure::Core::Nullable<std::string> Properties;
    Azure::Core::Nullable<std::string> LeaseDuration;
    LeaseStateType LeaseState = LeaseStateType::Unknown;
    LeaseStatusType LeaseStatus = LeaseStatusType::Unknown;
    Azure::Core::Nullable<std::string> ContentMd5;
  };

  struct PathGetPropertiesResult
  {
    Azure::Core::Nullable<std::string> AcceptRanges;
    DataLakeHttpHeaders HttpHeaders;
    int64_t ContentLength = int64_t();
    Azure::Core::Nullable<std::string> ContentRange;
    Azure::Core::Nullable<std::string> ContentMd5;
    std::string ETag;
    std::string LastModified;
    Azure::Core::Nullable<std::string> ResourceType;
    Azure::Core::Nullable<std::string> Properties;
    Azure::Core::Nullable<std::string> Owner;
    Azure::Core::Nullable<std::string> Group;
    Azure::Core::Nullable<std::string> Permissions;
    Azure::Core::Nullable<std::string> Acl;
    Azure::Core::Nullable<std::string> LeaseDuration;
    Azure::Core::Nullable<LeaseStateType> LeaseState;
    Azure::Core::Nullable<LeaseStatusType> LeaseStatus;
  };

  struct PathDeleteResult
  {
    Azure::Core::Nullable<std::string> ContinuationToken;
  };

  struct PathSetAccessControlResult
  {
    std::string ETag;
    std::string LastModified;
  };

  struct PathSetAccessControlRecursiveResult
  {
    Azure::Core::Nullable<std::string> ContinuationToken;
    int32_t DirectoriesSuccessful = int32_t();
    int32_t FilesSuccessful = int32_t();
    int32_t FailureCount = int32_t();
    std::vector<AclFailedEntry> FailedEntries;
  };

  struct PathFlushDataResult
  {
    std::string ETag;
    std::string LastModified;
    int64_t ContentLength = int64_t();
  };

  struct PathAppendDataResult
  {
    Azure::Core::Nullable<std::string> ContentMD5;
    Azure::Core::Nullable<std::string> ContentCrc64;
    bool IsServerEncrypted = bool();
  };

  struct PathSetExpiryResult
  {
    std::string ETag;
    std::string LastModified;
  };

  namespace Details {
    inline std::string PathSetAccessControlRecursiveModeToString(
        const PathSetAccessControlRecursiveMode& pathSetAccessControlRecursiveMode)
    {
      switch (pathSetAccessControlRecursiveMode)
      {
        case PathSetAccessControlRecursiveMode::Set:
          return "set";
        case PathSetAccessControlRecursiveMode::Modify:
          return "modify";
        case PathSetAccessControlRecursiveMode::Remove:
          return "remove";
        default:
          return std::string();
      }
    }

    inline PathSetAccessControlRecursiveMode PathSetAccessControlRecursiveModeFromString(
        const std::string& pathSetAccessControlRecursiveMode)
    {
      if (pathSetAccessControlRecursiveMode == "set")
      {
        return PathSetAccessControlRecursiveMode::Set;
      }
      if (pathSetAccessControlRecursiveMode == "modify")
      {
        return PathSetAccessControlRecursiveMode::Modify;
      }
      if (pathSetAccessControlRecursiveMode == "remove")
      {
        return PathSetAccessControlRecursiveMode::Remove;
      }
      throw std::runtime_error(
          "Cannot convert " + pathSetAccessControlRecursiveMode
          + " to PathSetAccessControlRecursiveMode");
    }

    inline std::string PathExpiryOptionsToString(const PathExpiryOptions& pathExpiryOptions)
    {
      switch (pathExpiryOptions)
      {
        case PathExpiryOptions::NeverExpire:
          return "NeverExpire";
        case PathExpiryOptions::RelativeToCreation:
          return "RelativeToCreation";
        case PathExpiryOptions::RelativeToNow:
          return "RelativeToNow";
        case PathExpiryOptions::Absolute:
          return "Absolute";
        default:
          return std::string();
      }
    }

    inline PathExpiryOptions PathExpiryOptionsFromString(const std::string& pathExpiryOptions)
    {
      if (pathExpiryOptions == "NeverExpire")
      {
        return PathExpiryOptions::NeverExpire;
      }
      if (pathExpiryOptions == "RelativeToCreation")
      {
        return PathExpiryOptions::RelativeToCreation;
      }
      if (pathExpiryOptions == "RelativeToNow")
      {
        return PathExpiryOptions::RelativeToNow;
      }
      if (pathExpiryOptions == "Absolute")
      {
        return PathExpiryOptions::Absolute;
      }
      throw std::runtime_error("Cannot convert " + pathExpiryOptions + " to PathExpiryOptions");
    }

    inline std::string PathResourceTypeToString(const PathResourceType& pathResourceType)
    {
      switch (pathResourceType)
      {
        case PathResourceType::Directory:
          return "directory";
        case PathResourceType::File:
          return "file";
        default:
          return std::string();
      }
    }

    inline PathResourceType PathResourceTypeFromString(const std::string& pathResourceType)
    {
      if (pathResourceType == "directory")
      {
        return PathResourceType::Directory;
      }
      if (pathResourceType == "file")
      {
        return PathResourceType::File;
      }
      throw std::runtime_error("Cannot convert " + pathResourceType + " to PathResourceType");
    }

    inline std::string PathRenameModeToString(const PathRenameMode& pathRenameMode)
    {
      switch (pathRenameMode)
      {
        case PathRenameMode::Legacy:
          return "legacy";
        case PathRenameMode::Posix:
          return "posix";
        default:
          return std::string();
      }
    }

    inline PathRenameMode PathRenameModeFromString(const std::string& pathRenameMode)
    {
      if (pathRenameMode == "legacy")
      {
        return PathRenameMode::Legacy;
      }
      if (pathRenameMode == "posix")
      {
        return PathRenameMode::Posix;
      }
      throw std::runtime_error("Cannot convert " + pathRenameMode + " to PathRenameMode");
    }

    inline std::string PathLeaseActionToString(const PathLeaseAction& pathLeaseAction)
    {
      switch (pathLeaseAction)
      {
        case PathLeaseAction::Acquire:
          return "acquire";
        case PathLeaseAction::Break:
          return "break";
        case PathLeaseAction::Change:
          return "change";
        case PathLeaseAction::Renew:
          return "renew";
        case PathLeaseAction::Release:
          return "release";
        default:
          return std::string();
      }
    }

    inline PathLeaseAction PathLeaseActionFromString(const std::string& pathLeaseAction)
    {
      if (pathLeaseAction == "acquire")
      {
        return PathLeaseAction::Acquire;
      }
      if (pathLeaseAction == "break")
      {
        return PathLeaseAction::Break;
      }
      if (pathLeaseAction == "change")
      {
        return PathLeaseAction::Change;
      }
      if (pathLeaseAction == "renew")
      {
        return PathLeaseAction::Renew;
      }
      if (pathLeaseAction == "release")
      {
        return PathLeaseAction::Release;
      }
      throw std::runtime_error("Cannot convert " + pathLeaseAction + " to PathLeaseAction");
    }

    inline std::string LeaseStateTypeToString(const LeaseStateType& leaseStateType)
    {
      switch (leaseStateType)
      {
        case LeaseStateType::Available:
          return "available";
        case LeaseStateType::Leased:
          return "leased";
        case LeaseStateType::Expired:
          return "expired";
        case LeaseStateType::Breaking:
          return "breaking";
        case LeaseStateType::Broken:
          return "broken";
        default:
          return std::string();
      }
    }

    inline LeaseStateType LeaseStateTypeFromString(const std::string& leaseStateType)
    {
      if (leaseStateType == "available")
      {
        return LeaseStateType::Available;
      }
      if (leaseStateType == "leased")
      {
        return LeaseStateType::Leased;
      }
      if (leaseStateType == "expired")
      {
        return LeaseStateType::Expired;
      }
      if (leaseStateType == "breaking")
      {
        return LeaseStateType::Breaking;
      }
      if (leaseStateType == "broken")
      {
        return LeaseStateType::Broken;
      }
      throw std::runtime_error("Cannot convert " + leaseStateType + " to LeaseStateType");
    }

    inline std::string LeaseStatusTypeToString(const LeaseStatusType& leaseStatusType)
    {
      switch (leaseStatusType)
      {
        case LeaseStatusType::Locked:
          return "locked";
        case LeaseStatusType::Unlocked:
          return "unlocked";
        default:
          return std::string();
      }
    }

    inline LeaseStatusType LeaseStatusTypeFromString(const std::string& leaseStatusType)
    {
      if (leaseStatusType == "locked")
      {
        return LeaseStatusType::Locked;
      }
      if (leaseStatusType == "unlocked")
      {
        return LeaseStatusType::Unlocked;
      }
      throw std::runtime_error("Cannot convert " + leaseStatusType + " to LeaseStatusType");
    }

    inline std::string PathGetPropertiesActionToString(
        const PathGetPropertiesAction& pathGetPropertiesAction)
    {
      switch (pathGetPropertiesAction)
      {
        case PathGetPropertiesAction::GetAccessControl:
          return "getAccessControl";
        case PathGetPropertiesAction::GetStatus:
          return "getStatus";
        default:
          return std::string();
      }
    }

    inline PathGetPropertiesAction PathGetPropertiesActionFromString(
        const std::string& pathGetPropertiesAction)
    {
      if (pathGetPropertiesAction == "getAccessControl")
      {
        return PathGetPropertiesAction::GetAccessControl;
      }
      if (pathGetPropertiesAction == "getStatus")
      {
        return PathGetPropertiesAction::GetStatus;
      }
      throw std::runtime_error(
          "Cannot convert " + pathGetPropertiesAction + " to PathGetPropertiesAction");
    }

    class DataLakeRestClient {
    public:
      class Service {
      public:
        struct ListFileSystemsOptions
        {
          Azure::Core::Nullable<std::string>
              Prefix; // Filters results to filesystems within the specified prefix.
          Azure::Core::Nullable<std::string>
              ContinuationToken; // Optional.  When deleting a directory, the number of paths that
                                 // are deleted with each invocation is limited.  If the number of
                                 // paths to be deleted exceeds this limit, a continuation token is
                                 // returned in this response header.  When a continuation token is
                                 // returned in the response, it must be specified in a subsequent
                                 // invocation of the delete operation to continue deleting the
                                 // directory.
          Azure::Core::Nullable<int32_t>
              MaxResults; // An optional value that specifies the maximum number of items to return.
                          // If omitted or greater than 5,000, the response will include up to 5,000
                          // items.
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
        };

        static Azure::Core::Response<ServiceListFileSystemsResult> ListFileSystems(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const ListFileSystemsOptions& listFileSystemsOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
          request.GetUrl().AppendQueryParameter(Details::c_QueryResource, "account");
          if (listFileSystemsOptions.Prefix.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryPrefix,
                Storage::Details::UrlEncodeQueryParameter(
                    listFileSystemsOptions.Prefix.GetValue()));
          }
          if (listFileSystemsOptions.ContinuationToken.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryContinuationToken,
                Storage::Details::UrlEncodeQueryParameter(
                    listFileSystemsOptions.ContinuationToken.GetValue()));
          }
          if (listFileSystemsOptions.MaxResults.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryMaxResults,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(listFileSystemsOptions.MaxResults.GetValue())));
          }
          if (listFileSystemsOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId,
                listFileSystemsOptions.ClientRequestId.GetValue());
          }
          if (listFileSystemsOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(listFileSystemsOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, listFileSystemsOptions.ApiVersionParameter);
          return ListFileSystemsParseResult(context, pipeline.Send(context, request));
        }

      private:
        static Azure::Core::Response<ServiceListFileSystemsResult> ListFileSystemsParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // OK
            const auto& bodyBuffer = response.GetBody();
            ServiceListFileSystemsResult result = bodyBuffer.empty()
                ? ServiceListFileSystemsResult()
                : ServiceListFileSystemsResultFromFileSystemList(
                    FileSystemListFromJson(nlohmann::json::parse(bodyBuffer)));
            if (response.GetHeaders().find(Details::c_HeaderXMsContinuation)
                != response.GetHeaders().end())
            {
              result.ContinuationToken = response.GetHeaders().at(Details::c_HeaderXMsContinuation);
            }
            return Azure::Core::Response<ServiceListFileSystemsResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Storage::Files::DataLake::FileSystem FileSystemFromJson(const nlohmann::json& node)
        {
          Storage::Files::DataLake::FileSystem result;
          result.Name = node["name"].get<std::string>();
          result.LastModified = node["lastModified"].get<std::string>();
          result.ETag = node["etag"].get<std::string>();
          return result;
        }

        static Storage::Files::DataLake::FileSystemList FileSystemListFromJson(
            const nlohmann::json& node)
        {
          Storage::Files::DataLake::FileSystemList result;
          for (const auto& element : node["filesystems"])
          {
            result.Filesystems.emplace_back(FileSystemFromJson(element));
          }
          return result;
        }

        static ServiceListFileSystemsResult ServiceListFileSystemsResultFromFileSystemList(
            FileSystemList object)
        {
          ServiceListFileSystemsResult result;
          result.Filesystems = std::move(object.Filesystems);

          return result;
        }
      };

      class FileSystem {
      public:
        struct CreateOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<std::string>
              Properties; // Optional. User-defined properties to be stored with the filesystem, in
                          // the format of a comma-separated list of name and value pairs "n1=v1,
                          // n2=v2, ...", where each value is a base64 encoded string. Note that the
                          // string may only contain ASCII characters in the ISO-8859-1 character
                          // set.  If the filesystem exists, any properties not included in the list
                          // will be removed.  All properties are removed if the header is omitted.
                          // To merge new and existing properties, first get all existing properties
                          // and the current E-Tag, then make a conditional request with the E-Tag
                          // and include values for all properties.
        };

        static Azure::Core::Response<FileSystemCreateResult> Create(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const CreateOptions& createOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
          request.AddHeader(Details::c_HeaderContentLength, "0");
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryFileSystemResource,
              Storage::Details::UrlEncodeQueryParameter("filesystem"));
          if (createOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, createOptions.ClientRequestId.GetValue());
          }
          if (createOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(createOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, createOptions.ApiVersionParameter);
          if (createOptions.Properties.HasValue())
          {
            request.AddHeader(Details::c_HeaderProperties, createOptions.Properties.GetValue());
          }
          return CreateParseResult(context, pipeline.Send(context, request));
        }

        struct SetPropertiesOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<std::string>
              Properties; // Optional. User-defined properties to be stored with the filesystem, in
                          // the format of a comma-separated list of name and value pairs "n1=v1,
                          // n2=v2, ...", where each value is a base64 encoded string. Note that the
                          // string may only contain ASCII characters in the ISO-8859-1 character
                          // set.  If the filesystem exists, any properties not included in the list
                          // will be removed.  All properties are removed if the header is omitted.
                          // To merge new and existing properties, first get all existing properties
                          // and the current E-Tag, then make a conditional request with the E-Tag
                          // and include values for all properties.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
        };

        static Azure::Core::Response<FileSystemSetPropertiesResult> SetProperties(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const SetPropertiesOptions& setPropertiesOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryFileSystemResource,
              Storage::Details::UrlEncodeQueryParameter("filesystem"));
          if (setPropertiesOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, setPropertiesOptions.ClientRequestId.GetValue());
          }
          if (setPropertiesOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(setPropertiesOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, setPropertiesOptions.ApiVersionParameter);
          if (setPropertiesOptions.Properties.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderProperties, setPropertiesOptions.Properties.GetValue());
          }
          if (setPropertiesOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, setPropertiesOptions.IfModifiedSince.GetValue());
          }
          if (setPropertiesOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince,
                setPropertiesOptions.IfUnmodifiedSince.GetValue());
          }
          return SetPropertiesParseResult(context, pipeline.Send(context, request));
        }

        struct GetPropertiesOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
        };

        static Azure::Core::Response<FileSystemGetPropertiesResult> GetProperties(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const GetPropertiesOptions& getPropertiesOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Head, url);
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryFileSystemResource,
              Storage::Details::UrlEncodeQueryParameter("filesystem"));
          if (getPropertiesOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, getPropertiesOptions.ClientRequestId.GetValue());
          }
          if (getPropertiesOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(getPropertiesOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, getPropertiesOptions.ApiVersionParameter);
          return GetPropertiesParseResult(context, pipeline.Send(context, request));
        }

        struct DeleteOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
        };

        static Azure::Core::Response<FileSystemDeleteResult> Delete(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const DeleteOptions& deleteOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryFileSystemResource,
              Storage::Details::UrlEncodeQueryParameter("filesystem"));
          if (deleteOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, deleteOptions.ClientRequestId.GetValue());
          }
          if (deleteOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(deleteOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, deleteOptions.ApiVersionParameter);
          if (deleteOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, deleteOptions.IfModifiedSince.GetValue());
          }
          if (deleteOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince, deleteOptions.IfUnmodifiedSince.GetValue());
          }
          return DeleteParseResult(context, pipeline.Send(context, request));
        }

        struct ListPathsOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<std::string>
              ContinuationToken; // Optional.  When deleting a directory, the number of paths that
                                 // are deleted with each invocation is limited.  If the number of
                                 // paths to be deleted exceeds this limit, a continuation token is
                                 // returned in this response header.  When a continuation token is
                                 // returned in the response, it must be specified in a subsequent
                                 // invocation of the delete operation to continue deleting the
                                 // directory.
          Azure::Core::Nullable<std::string>
              Directory; // Optional.  Filters results to paths within the specified directory. An
                         // error occurs if the directory does not exist.
          bool RecursiveRequired = bool(); // Required
          Azure::Core::Nullable<int32_t>
              MaxResults; // An optional value that specifies the maximum number of items to return.
                          // If omitted or greater than 5,000, the response will include up to 5,000
                          // items.
          Azure::Core::Nullable<bool>
              Upn; // Optional. Valid only when Hierarchical Namespace is enabled for the account.
                   // If "true", the user identity values returned in the x-ms-owner, x-ms-group,
                   // and x-ms-acl response headers will be transformed from Azure Active Directory
                   // Object IDs to User Principal Names.  If "false", the values will be returned
                   // as Azure Active Directory Object IDs. The default value is false. Note that
                   // group and application Object IDs are not translated because they do not have
                   // unique friendly names.
        };

        static Azure::Core::Response<FileSystemListPathsResult> ListPaths(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const ListPathsOptions& listPathsOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryFileSystemResource,
              Storage::Details::UrlEncodeQueryParameter("filesystem"));
          if (listPathsOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, listPathsOptions.ClientRequestId.GetValue());
          }
          if (listPathsOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(listPathsOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, listPathsOptions.ApiVersionParameter);
          if (listPathsOptions.ContinuationToken.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryContinuationToken,
                Storage::Details::UrlEncodeQueryParameter(
                    listPathsOptions.ContinuationToken.GetValue()));
          }
          if (listPathsOptions.Directory.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryDirectory,
                Storage::Details::UrlEncodeQueryParameter(listPathsOptions.Directory.GetValue()));
          }
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryRecursiveRequired,
              Storage::Details::UrlEncodeQueryParameter(
                  (listPathsOptions.RecursiveRequired ? "true" : "false")));
          if (listPathsOptions.MaxResults.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryMaxResults,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(listPathsOptions.MaxResults.GetValue())));
          }
          if (listPathsOptions.Upn.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryUpn,
                Storage::Details::UrlEncodeQueryParameter(
                    (listPathsOptions.Upn.GetValue() ? "true" : "false")));
          }
          return ListPathsParseResult(context, pipeline.Send(context, request));
        }

      private:
        static Azure::Core::Response<FileSystemCreateResult> CreateParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
          {
            // Created
            FileSystemCreateResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            result.NamespaceEnabled
                = response.GetHeaders().at(Details::c_HeaderXMsNamespaceEnabled);
            return Azure::Core::Response<FileSystemCreateResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<FileSystemSetPropertiesResult> SetPropertiesParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Ok
            FileSystemSetPropertiesResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            return Azure::Core::Response<FileSystemSetPropertiesResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<FileSystemGetPropertiesResult> GetPropertiesParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Ok
            FileSystemGetPropertiesResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            result.Properties = response.GetHeaders().at(Details::c_HeaderXMsProperties);
            result.NamespaceEnabled
                = response.GetHeaders().at(Details::c_HeaderXMsNamespaceEnabled);
            return Azure::Core::Response<FileSystemGetPropertiesResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<FileSystemDeleteResult> DeleteParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
          {
            // Accepted
            FileSystemDeleteResult result;
            return Azure::Core::Response<FileSystemDeleteResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<FileSystemListPathsResult> ListPathsParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Ok
            const auto& bodyBuffer = response.GetBody();
            FileSystemListPathsResult result = bodyBuffer.empty()
                ? FileSystemListPathsResult()
                : FileSystemListPathsResultFromPathList(
                    PathListFromJson(nlohmann::json::parse(bodyBuffer)));
            if (response.GetHeaders().find(Details::c_HeaderXMsContinuation)
                != response.GetHeaders().end())
            {
              result.ContinuationToken = response.GetHeaders().at(Details::c_HeaderXMsContinuation);
            }
            return Azure::Core::Response<FileSystemListPathsResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Storage::Files::DataLake::Path PathFromJson(const nlohmann::json& node)
        {
          Storage::Files::DataLake::Path result;
          result.Name = node["name"].get<std::string>();
          if (node.contains("isDirectory"))
          {
            result.IsDirectory = (node["isDirectory"].get<std::string>() == "true");
          }
          result.LastModified = node["lastModified"].get<std::string>();
          result.ETag = node["etag"].get<std::string>();
          if (node.contains("contentLength"))
          {
            result.ContentLength = std::stoll(node["contentLength"].get<std::string>());
          }
          result.Owner = node["owner"].get<std::string>();
          result.Group = node["group"].get<std::string>();
          result.Permissions = node["permissions"].get<std::string>();
          return result;
        }

        static Storage::Files::DataLake::PathList PathListFromJson(const nlohmann::json& node)
        {
          Storage::Files::DataLake::PathList result;
          for (const auto& element : node["paths"])
          {
            result.Paths.emplace_back(PathFromJson(element));
          }
          return result;
        }

        static FileSystemListPathsResult FileSystemListPathsResultFromPathList(PathList object)
        {
          FileSystemListPathsResult result;
          result.Paths = std::move(object.Paths);

          return result;
        }
      };

      class Path {
      public:
        struct CreateOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<PathResourceType>
              Resource; // Required only for Create File and Create Directory. The value must be
                        // "file" or "directory".
          Azure::Core::Nullable<std::string>
              ContinuationToken; // Optional.  When deleting a directory, the number of paths that
                                 // are deleted with each invocation is limited.  If the number of
                                 // paths to be deleted exceeds this limit, a continuation token is
                                 // returned in this response header.  When a continuation token is
                                 // returned in the response, it must be specified in a subsequent
                                 // invocation of the delete operation to continue deleting the
                                 // directory.
          Azure::Core::Nullable<PathRenameMode>
              Mode; // Optional. Valid only when namespace is enabled. This parameter determines the
                    // behavior of the rename operation. The value must be "legacy" or "posix", and
                    // the default value will be "posix".
          Azure::Core::Nullable<std::string>
              CacheControl; // Optional. Sets the blob's cache control. If specified, this property
                            // is stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              ContentEncoding; // Optional. Sets the blob's content encoding. If specified, this
                               // property is stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              ContentLanguage; // Optional. Set the blob's content language. If specified, this
                               // property is stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              ContentDisposition; // Optional. Sets the blob's Content-Disposition header.
          Azure::Core::Nullable<std::string>
              ContentType; // Optional. Sets the blob's content type. If specified, this property is
                           // stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              RenameSource; // An optional file or directory to be renamed.  The value must have the
                            // following format: "/{filesystem}/{path}".  If "x-ms-properties" is
                            // specified, the properties will overwrite the existing properties;
                            // otherwise, the existing properties will be preserved. This value must
                            // be a URL percent-encoded string. Note that the string may only
                            // contain ASCII characters in the ISO-8859-1 character set.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string>
              SourceLeaseId; // A lease ID for the source path. If specified, the source path must
                             // have an active lease and the lease ID must match.
          Azure::Core::Nullable<std::string>
              Properties; // Optional. User-defined properties to be stored with the filesystem, in
                          // the format of a comma-separated list of name and value pairs "n1=v1,
                          // n2=v2, ...", where each value is a base64 encoded string. Note that the
                          // string may only contain ASCII characters in the ISO-8859-1 character
                          // set.  If the filesystem exists, any properties not included in the list
                          // will be removed.  All properties are removed if the header is omitted.
                          // To merge new and existing properties, first get all existing properties
                          // and the current E-Tag, then make a conditional request with the E-Tag
                          // and include values for all properties.
          Azure::Core::Nullable<std::string>
              Permissions; // Optional and only valid if Hierarchical Namespace is enabled for the
                           // account. Sets POSIX access permissions for the file owner, the file
                           // owning group, and others. Each class may be granted read, write, or
                           // execute permission.  The sticky bit is also supported.  Both symbolic
                           // (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
          Azure::Core::Nullable<std::string>
              Umask; // Optional and only valid if Hierarchical Namespace is enabled for the
                     // account. When creating a file or directory and the parent folder does not
                     // have a default ACL, the umask restricts the permissions of the file or
                     // directory to be created.  The resulting permission is given by p bitwise and
                     // not u, where p is the permission and u is the umask.  For example, if p is
                     // 0777 and u is 0057, then the resulting permission is 0720.  The default
                     // permission is 0777 for a directory and 0666 for a file.  The default umask
                     // is 0027.  The umask must be specified in 4-digit octal notation (e.g. 0766).
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
          Azure::Core::Nullable<std::string> SourceIfMatch; // Specify an ETag value to operate only
                                                            // on blobs with a matching value.
          Azure::Core::Nullable<std::string>
              SourceIfNoneMatch; // Specify an ETag value to operate only on blobs without a
                                 // matching value.
          Azure::Core::Nullable<std::string>
              SourceIfModifiedSince; // Specify this header value to operate only on a blob if it
                                     // has been modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              SourceIfUnmodifiedSince; // Specify this header value to operate only on a blob if it
                                       // has not been modified since the specified date/time.
        };

        static Azure::Core::Response<PathCreateResult> Create(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const CreateOptions& createOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
          request.AddHeader(Details::c_HeaderContentLength, "0");
          if (createOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, createOptions.ClientRequestId.GetValue());
          }
          if (createOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(createOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, createOptions.ApiVersionParameter);
          if (createOptions.Resource.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryPathResourceType,
                Storage::Details::UrlEncodeQueryParameter(
                    PathResourceTypeToString(createOptions.Resource.GetValue())));
          }
          if (createOptions.ContinuationToken.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryContinuationToken,
                Storage::Details::UrlEncodeQueryParameter(
                    createOptions.ContinuationToken.GetValue()));
          }
          if (createOptions.Mode.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryPathRenameMode,
                Storage::Details::UrlEncodeQueryParameter(
                    PathRenameModeToString(createOptions.Mode.GetValue())));
          }
          if (createOptions.CacheControl.HasValue())
          {
            request.AddHeader(Details::c_HeaderCacheControl, createOptions.CacheControl.GetValue());
          }
          if (createOptions.ContentEncoding.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentEncoding, createOptions.ContentEncoding.GetValue());
          }
          if (createOptions.ContentLanguage.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentLanguage, createOptions.ContentLanguage.GetValue());
          }
          if (createOptions.ContentDisposition.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentDisposition, createOptions.ContentDisposition.GetValue());
          }
          if (createOptions.ContentType.HasValue())
          {
            request.AddHeader(Details::c_HeaderContentType, createOptions.ContentType.GetValue());
          }
          if (createOptions.RenameSource.HasValue())
          {
            request.AddHeader(Details::c_HeaderRenameSource, createOptions.RenameSource.GetValue());
          }
          if (createOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, createOptions.LeaseIdOptional.GetValue());
          }
          if (createOptions.SourceLeaseId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderSourceLeaseId, createOptions.SourceLeaseId.GetValue());
          }
          if (createOptions.Properties.HasValue())
          {
            request.AddHeader(Details::c_HeaderProperties, createOptions.Properties.GetValue());
          }
          if (createOptions.Permissions.HasValue())
          {
            request.AddHeader(Details::c_HeaderPermissions, createOptions.Permissions.GetValue());
          }
          if (createOptions.Umask.HasValue())
          {
            request.AddHeader(Details::c_HeaderUmask, createOptions.Umask.GetValue());
          }
          if (createOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, createOptions.IfMatch.GetValue());
          }
          if (createOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfNoneMatch, createOptions.IfNoneMatch.GetValue());
          }
          if (createOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, createOptions.IfModifiedSince.GetValue());
          }
          if (createOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince, createOptions.IfUnmodifiedSince.GetValue());
          }
          if (createOptions.SourceIfMatch.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderSourceIfMatch, createOptions.SourceIfMatch.GetValue());
          }
          if (createOptions.SourceIfNoneMatch.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderSourceIfNoneMatch, createOptions.SourceIfNoneMatch.GetValue());
          }
          if (createOptions.SourceIfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderSourceIfModifiedSince,
                createOptions.SourceIfModifiedSince.GetValue());
          }
          if (createOptions.SourceIfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderSourceIfUnmodifiedSince,
                createOptions.SourceIfUnmodifiedSince.GetValue());
          }
          return CreateParseResult(context, pipeline.Send(context, request));
        }

        struct LeaseOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          PathLeaseAction
              XMsLeaseAction; // There are five lease actions: "acquire", "break", "change",
                              // "renew", and "release". Use "acquire" and specify the
                              // "x-ms-proposed-lease-id" and "x-ms-lease-duration" to acquire a new
                              // lease. Use "break" to break an existing lease. When a lease is
                              // broken, the lease break period is allowed to elapse, during which
                              // time no lease operation except break and release can be performed
                              // on the file. When a lease is successfully broken, the response
                              // indicates the interval in seconds until a new lease can be
                              // acquired. Use "change" and specify the current lease ID in
                              // "x-ms-lease-id" and the new lease ID in "x-ms-proposed-lease-id" to
                              // change the lease ID of an active lease. Use "renew" and specify the
                              // "x-ms-lease-id" to renew an existing lease. Use "release" and
                              // specify the "x-ms-lease-id" to release a lease.
          Azure::Core::Nullable<int32_t>
              XMsLeaseDuration; // The lease duration is required to acquire a lease, and specifies
                                // the duration of the lease in seconds.  The lease duration must be
                                // between 15 and 60 seconds or -1 for infinite lease.
          Azure::Core::Nullable<int32_t>
              XMsLeaseBreakPeriod; // The lease break period duration is optional to break a lease,
                                   // and  specifies the break period of the lease in seconds.  The
                                   // lease break  duration must be between 0 and 60 seconds.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string>
              ProposedLeaseIdOptional; // Proposed lease ID, in a GUID string format. The Blob
                                       // service returns 400 (Invalid request) if the proposed
                                       // lease ID is not in the correct format. See Guid
                                       // Constructor (String) for a list of valid GUID string
                                       // formats.
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
        };

        static Azure::Core::Response<PathLeaseResult> Lease(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const LeaseOptions& leaseOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Post, url);
          request.AddHeader(Details::c_HeaderContentLength, "0");
          if (leaseOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, leaseOptions.ClientRequestId.GetValue());
          }
          if (leaseOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(leaseOptions.Timeout.GetValue())));
          }
          request.AddHeader(Details::c_HeaderApiVersionParameter, leaseOptions.ApiVersionParameter);
          request.AddHeader(
              Details::c_HeaderPathLeaseAction,
              PathLeaseActionToString(leaseOptions.XMsLeaseAction));
          if (leaseOptions.XMsLeaseDuration.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderXMsLeaseDuration,
                std::to_string(leaseOptions.XMsLeaseDuration.GetValue()));
          }
          if (leaseOptions.XMsLeaseBreakPeriod.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderXMsLeaseBreakPeriod,
                std::to_string(leaseOptions.XMsLeaseBreakPeriod.GetValue()));
          }
          if (leaseOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, leaseOptions.LeaseIdOptional.GetValue());
          }
          if (leaseOptions.ProposedLeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderProposedLeaseIdOptional,
                leaseOptions.ProposedLeaseIdOptional.GetValue());
          }
          if (leaseOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, leaseOptions.IfMatch.GetValue());
          }
          if (leaseOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfNoneMatch, leaseOptions.IfNoneMatch.GetValue());
          }
          if (leaseOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, leaseOptions.IfModifiedSince.GetValue());
          }
          if (leaseOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince, leaseOptions.IfUnmodifiedSince.GetValue());
          }
          return LeaseParseResult(context, pipeline.Send(context, request));
        }

        struct ReadOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<std::string>
              Range; // The HTTP Range request header specifies one or more byte ranges of the
                     // resource to be retrieved.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<bool>
              XMsRangeGetContentMd5; // Optional. When this header is set to "true" and specified
                                     // together with the Range header, the service returns the MD5
                                     // hash for the range, as long as the range is less than or
                                     // equal to 4MB in size. If this header is specified without
                                     // the Range header, the service returns status code 400 (Bad
                                     // Request). If this header is set to true when the range
                                     // exceeds 4 MB in size, the service returns status code 400
                                     // (Bad Request).
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
        };

        static Azure::Core::Response<PathReadResult> Read(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const ReadOptions& readOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url, true);
          if (readOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, readOptions.ClientRequestId.GetValue());
          }
          if (readOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(readOptions.Timeout.GetValue())));
          }
          request.AddHeader(Details::c_HeaderApiVersionParameter, readOptions.ApiVersionParameter);
          if (readOptions.Range.HasValue())
          {
            request.AddHeader(Details::c_HeaderRange, readOptions.Range.GetValue());
          }
          if (readOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, readOptions.LeaseIdOptional.GetValue());
          }
          if (readOptions.XMsRangeGetContentMd5.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderXMsRangeGetContentMd5,
                (readOptions.XMsRangeGetContentMd5.GetValue() ? "true" : "false"));
          }
          if (readOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, readOptions.IfMatch.GetValue());
          }
          if (readOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfNoneMatch, readOptions.IfNoneMatch.GetValue());
          }
          if (readOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, readOptions.IfModifiedSince.GetValue());
          }
          if (readOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince, readOptions.IfUnmodifiedSince.GetValue());
          }
          return ReadParseResult(context, pipeline.Send(context, request));
        }

        struct GetPropertiesOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<PathGetPropertiesAction>
              Action; // Optional. If the value is "getStatus" only the system defined properties
                      // for the path are returned. If the value is "getAccessControl" the access
                      // control list is returned in the response headers (Hierarchical Namespace
                      // must be enabled for the account), otherwise the properties are returned.
          Azure::Core::Nullable<bool>
              Upn; // Optional. Valid only when Hierarchical Namespace is enabled for the account.
                   // If "true", the user identity values returned in the x-ms-owner, x-ms-group,
                   // and x-ms-acl response headers will be transformed from Azure Active Directory
                   // Object IDs to User Principal Names.  If "false", the values will be returned
                   // as Azure Active Directory Object IDs. The default value is false. Note that
                   // group and application Object IDs are not translated because they do not have
                   // unique friendly names.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
        };

        static Azure::Core::Response<PathGetPropertiesResult> GetProperties(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const GetPropertiesOptions& getPropertiesOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Head, url);
          if (getPropertiesOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, getPropertiesOptions.ClientRequestId.GetValue());
          }
          if (getPropertiesOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(getPropertiesOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, getPropertiesOptions.ApiVersionParameter);
          if (getPropertiesOptions.Action.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryPathGetPropertiesAction,
                Storage::Details::UrlEncodeQueryParameter(
                    PathGetPropertiesActionToString(getPropertiesOptions.Action.GetValue())));
          }
          if (getPropertiesOptions.Upn.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryUpn,
                Storage::Details::UrlEncodeQueryParameter(
                    (getPropertiesOptions.Upn.GetValue() ? "true" : "false")));
          }
          if (getPropertiesOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, getPropertiesOptions.LeaseIdOptional.GetValue());
          }
          if (getPropertiesOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, getPropertiesOptions.IfMatch.GetValue());
          }
          if (getPropertiesOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfNoneMatch, getPropertiesOptions.IfNoneMatch.GetValue());
          }
          if (getPropertiesOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, getPropertiesOptions.IfModifiedSince.GetValue());
          }
          if (getPropertiesOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince,
                getPropertiesOptions.IfUnmodifiedSince.GetValue());
          }
          return GetPropertiesParseResult(context, pipeline.Send(context, request));
        }

        struct DeleteOptions
        {
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<bool> RecursiveOptional; // Required
          Azure::Core::Nullable<std::string>
              ContinuationToken; // Optional.  When deleting a directory, the number of paths that
                                 // are deleted with each invocation is limited.  If the number of
                                 // paths to be deleted exceeds this limit, a continuation token is
                                 // returned in this response header.  When a continuation token is
                                 // returned in the response, it must be specified in a subsequent
                                 // invocation of the delete operation to continue deleting the
                                 // directory.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
        };

        static Azure::Core::Response<PathDeleteResult> Delete(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const DeleteOptions& deleteOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
          if (deleteOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, deleteOptions.ClientRequestId.GetValue());
          }
          if (deleteOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(deleteOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, deleteOptions.ApiVersionParameter);
          if (deleteOptions.RecursiveOptional.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryRecursiveOptional,
                Storage::Details::UrlEncodeQueryParameter(
                    (deleteOptions.RecursiveOptional.GetValue() ? "true" : "false")));
          }
          if (deleteOptions.ContinuationToken.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryContinuationToken,
                Storage::Details::UrlEncodeQueryParameter(
                    deleteOptions.ContinuationToken.GetValue()));
          }
          if (deleteOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, deleteOptions.LeaseIdOptional.GetValue());
          }
          if (deleteOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, deleteOptions.IfMatch.GetValue());
          }
          if (deleteOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfNoneMatch, deleteOptions.IfNoneMatch.GetValue());
          }
          if (deleteOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, deleteOptions.IfModifiedSince.GetValue());
          }
          if (deleteOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince, deleteOptions.IfUnmodifiedSince.GetValue());
          }
          return DeleteParseResult(context, pipeline.Send(context, request));
        }

        struct SetAccessControlOptions
        {
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string> Owner; // Optional. The owner of the blob or directory.
          Azure::Core::Nullable<std::string>
              Group; // Optional. The owning group of the blob or directory.
          Azure::Core::Nullable<std::string>
              Permissions; // Optional and only valid if Hierarchical Namespace is enabled for the
                           // account. Sets POSIX access permissions for the file owner, the file
                           // owning group, and others. Each class may be granted read, write, or
                           // execute permission.  The sticky bit is also supported.  Both symbolic
                           // (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
          Azure::Core::Nullable<std::string>
              Acl; // Sets POSIX access control rights on files and directories. The value is a
                   // comma-separated list of access control entries. Each access control entry
                   // (ACE) consists of a scope, a type, a user or group identifier, and permissions
                   // in the format "[scope:][type]:[id]:[permissions]".
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
        };

        static Azure::Core::Response<PathSetAccessControlResult> SetAccessControl(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const SetAccessControlOptions& setAccessControlOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
          request.GetUrl().AppendQueryParameter(Details::c_QueryAction, "setAccessControl");
          if (setAccessControlOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(setAccessControlOptions.Timeout.GetValue())));
          }
          if (setAccessControlOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional,
                setAccessControlOptions.LeaseIdOptional.GetValue());
          }
          if (setAccessControlOptions.Owner.HasValue())
          {
            request.AddHeader(Details::c_HeaderOwner, setAccessControlOptions.Owner.GetValue());
          }
          if (setAccessControlOptions.Group.HasValue())
          {
            request.AddHeader(Details::c_HeaderGroup, setAccessControlOptions.Group.GetValue());
          }
          if (setAccessControlOptions.Permissions.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderPermissions, setAccessControlOptions.Permissions.GetValue());
          }
          if (setAccessControlOptions.Acl.HasValue())
          {
            request.AddHeader(Details::c_HeaderAcl, setAccessControlOptions.Acl.GetValue());
          }
          if (setAccessControlOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, setAccessControlOptions.IfMatch.GetValue());
          }
          if (setAccessControlOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfNoneMatch, setAccessControlOptions.IfNoneMatch.GetValue());
          }
          if (setAccessControlOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince,
                setAccessControlOptions.IfModifiedSince.GetValue());
          }
          if (setAccessControlOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince,
                setAccessControlOptions.IfUnmodifiedSince.GetValue());
          }
          if (setAccessControlOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId,
                setAccessControlOptions.ClientRequestId.GetValue());
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, setAccessControlOptions.ApiVersionParameter);
          return SetAccessControlParseResult(context, pipeline.Send(context, request));
        }

        struct SetAccessControlRecursiveOptions
        {
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          Azure::Core::Nullable<std::string>
              ContinuationToken; // Optional.  When deleting a directory, the number of paths that
                                 // are deleted with each invocation is limited.  If the number of
                                 // paths to be deleted exceeds this limit, a continuation token is
                                 // returned in this response header.  When a continuation token is
                                 // returned in the response, it must be specified in a subsequent
                                 // invocation of the delete operation to continue deleting the
                                 // directory.
          PathSetAccessControlRecursiveMode
              Mode; // Mode "set" sets POSIX access control rights on files and directories,
                    // "modify" modifies one or more POSIX access control rights  that pre-exist on
                    // files and directories, "remove" removes one or more POSIX access control
                    // rights  that were present earlier on files and directories
          Azure::Core::Nullable<bool>
              ForceFlag; // Optional. Valid for "SetAccessControlRecursive" operation. If set to
                         // false, the operation will terminate quickly on encountering user errors
                         // (4XX). If true, the operation will ignore user errors and proceed with
                         // the operation on other sub-entities of the directory. Continuation token
                         // will only be returned when forceFlag is true in case of user errors. If
                         // not set the default value is false for this.
          Azure::Core::Nullable<int32_t>
              MaxRecords; // Optional. It specifies the maximum number of files or directories on
                          // which the acl change will be applied. If omitted or greater than 2,000,
                          // the request will process up to 2,000 items
          Azure::Core::Nullable<std::string>
              Acl; // Sets POSIX access control rights on files and directories. The value is a
                   // comma-separated list of access control entries. Each access control entry
                   // (ACE) consists of a scope, a type, a user or group identifier, and permissions
                   // in the format "[scope:][type]:[id]:[permissions]".
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
        };

        static Azure::Core::Response<PathSetAccessControlRecursiveResult> SetAccessControlRecursive(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const SetAccessControlRecursiveOptions& setAccessControlRecursiveOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryAction, "setAccessControlRecursive");
          if (setAccessControlRecursiveOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(setAccessControlRecursiveOptions.Timeout.GetValue())));
          }
          if (setAccessControlRecursiveOptions.ContinuationToken.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryContinuationToken,
                Storage::Details::UrlEncodeQueryParameter(
                    setAccessControlRecursiveOptions.ContinuationToken.GetValue()));
          }
          request.GetUrl().AppendQueryParameter(
              Details::c_QueryPathSetAccessControlRecursiveMode,
              Storage::Details::UrlEncodeQueryParameter(PathSetAccessControlRecursiveModeToString(
                  setAccessControlRecursiveOptions.Mode)));
          if (setAccessControlRecursiveOptions.ForceFlag.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryForceFlag,
                Storage::Details::UrlEncodeQueryParameter(
                    (setAccessControlRecursiveOptions.ForceFlag.GetValue() ? "true" : "false")));
          }
          if (setAccessControlRecursiveOptions.MaxRecords.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryMaxRecords,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(setAccessControlRecursiveOptions.MaxRecords.GetValue())));
          }
          if (setAccessControlRecursiveOptions.Acl.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderAcl, setAccessControlRecursiveOptions.Acl.GetValue());
          }
          if (setAccessControlRecursiveOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId,
                setAccessControlRecursiveOptions.ClientRequestId.GetValue());
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter,
              setAccessControlRecursiveOptions.ApiVersionParameter);
          return SetAccessControlRecursiveParseResult(context, pipeline.Send(context, request));
        }

        struct FlushDataOptions
        {
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          Azure::Core::Nullable<int64_t>
              Position; // This parameter allows the caller to upload data in parallel and control
                        // the order in which it is appended to the file.  It is required when
                        // uploading data to be appended to the file and when flushing previously
                        // uploaded data to the file.  The value must be the position where the data
                        // is to be appended.  Uploaded data is not immediately flushed, or written,
                        // to the file.  To flush, the previously uploaded data must be contiguous,
                        // the position parameter must be specified and equal to the length of the
                        // file after all data has been written, and there must not be a request
                        // entity body included with the request.
          Azure::Core::Nullable<bool>
              RetainUncommittedData; // Valid only for flush operations.  If "true", uncommitted
                                     // data is retained after the flush operation completes;
                                     // otherwise, the uncommitted data is deleted after the flush
                                     // operation.  The default is false.  Data at offsets less than
                                     // the specified position are written to the file when flush
                                     // succeeds, but this optional parameter allows data after the
                                     // flush position to be retained for a future flush operation.
          Azure::Core::Nullable<bool>
              Close; // Azure Storage Events allow applications to receive notifications when files
                     // change. When Azure Storage Events are enabled, a file changed event is
                     // raised. This event has a property indicating whether this is the final
                     // change to distinguish the difference between an intermediate flush to a file
                     // stream and the final close of a file stream. The close query parameter is
                     // valid only when the action is "flush" and change notifications are enabled.
                     // If the value of close is "true" and the flush operation completes
                     // successfully, the service raises a file change notification with a property
                     // indicating that this is the final update (the file stream has been closed).
                     // If "false" a change notification is raised indicating the file has changed.
                     // The default is false. This query parameter is set to true by the Hadoop ABFS
                     // driver to indicate that the file stream has been closed."
          Azure::Core::Nullable<int64_t>
              ContentLength; // Required for "Append Data" and "Flush Data".  Must be 0 for "Flush
                             // Data".  Must be the length of the request content in bytes for
                             // "Append Data".
          Azure::Core::Nullable<std::string> ContentMd5; // Specify the transactional md5 for the
                                                         // body, to be validated by the service.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string>
              CacheControl; // Optional. Sets the blob's cache control. If specified, this property
                            // is stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              ContentType; // Optional. Sets the blob's content type. If specified, this property is
                           // stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              ContentDisposition; // Optional. Sets the blob's Content-Disposition header.
          Azure::Core::Nullable<std::string>
              ContentEncoding; // Optional. Sets the blob's content encoding. If specified, this
                               // property is stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              ContentLanguage; // Optional. Set the blob's content language. If specified, this
                               // property is stored with the blob and returned with a read request.
          Azure::Core::Nullable<std::string>
              IfMatch; // Specify an ETag value to operate only on blobs with a matching value.
          Azure::Core::Nullable<std::string> IfNoneMatch; // Specify an ETag value to operate only
                                                          // on blobs without a matching value.
          Azure::Core::Nullable<std::string>
              IfModifiedSince; // Specify this header value to operate only on a blob if it has been
                               // modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              IfUnmodifiedSince; // Specify this header value to operate only on a blob if it has
                                 // not been modified since the specified date/time.
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
        };

        static Azure::Core::Response<PathFlushDataResult> FlushData(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const FlushDataOptions& flushDataOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
          request.GetUrl().AppendQueryParameter(Details::c_QueryAction, "flush");
          if (flushDataOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(flushDataOptions.Timeout.GetValue())));
          }
          if (flushDataOptions.Position.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryPosition,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(flushDataOptions.Position.GetValue())));
          }
          if (flushDataOptions.RetainUncommittedData.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryRetainUncommittedData,
                Storage::Details::UrlEncodeQueryParameter(
                    (flushDataOptions.RetainUncommittedData.GetValue() ? "true" : "false")));
          }
          if (flushDataOptions.Close.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryClose,
                Storage::Details::UrlEncodeQueryParameter(
                    (flushDataOptions.Close.GetValue() ? "true" : "false")));
          }
          if (flushDataOptions.ContentLength.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentLength,
                std::to_string(flushDataOptions.ContentLength.GetValue()));
          }
          if (flushDataOptions.ContentMd5.HasValue())
          {
            request.AddHeader(Details::c_HeaderContentMd5, flushDataOptions.ContentMd5.GetValue());
          }
          if (flushDataOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, flushDataOptions.LeaseIdOptional.GetValue());
          }
          if (flushDataOptions.CacheControl.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderCacheControl, flushDataOptions.CacheControl.GetValue());
          }
          if (flushDataOptions.ContentType.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentType, flushDataOptions.ContentType.GetValue());
          }
          if (flushDataOptions.ContentDisposition.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentDisposition,
                flushDataOptions.ContentDisposition.GetValue());
          }
          if (flushDataOptions.ContentEncoding.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentEncoding, flushDataOptions.ContentEncoding.GetValue());
          }
          if (flushDataOptions.ContentLanguage.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentLanguage, flushDataOptions.ContentLanguage.GetValue());
          }
          if (flushDataOptions.IfMatch.HasValue())
          {
            request.AddHeader(Details::c_HeaderIfMatch, flushDataOptions.IfMatch.GetValue());
          }
          if (flushDataOptions.IfNoneMatch.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfNoneMatch, flushDataOptions.IfNoneMatch.GetValue());
          }
          if (flushDataOptions.IfModifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfModifiedSince, flushDataOptions.IfModifiedSince.GetValue());
          }
          if (flushDataOptions.IfUnmodifiedSince.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderIfUnmodifiedSince, flushDataOptions.IfUnmodifiedSince.GetValue());
          }
          if (flushDataOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, flushDataOptions.ClientRequestId.GetValue());
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, flushDataOptions.ApiVersionParameter);
          return FlushDataParseResult(context, pipeline.Send(context, request));
        }

        struct AppendDataOptions
        {
          Azure::Core::Nullable<int64_t>
              Position; // This parameter allows the caller to upload data in parallel and control
                        // the order in which it is appended to the file.  It is required when
                        // uploading data to be appended to the file and when flushing previously
                        // uploaded data to the file.  The value must be the position where the data
                        // is to be appended.  Uploaded data is not immediately flushed, or written,
                        // to the file.  To flush, the previously uploaded data must be contiguous,
                        // the position parameter must be specified and equal to the length of the
                        // file after all data has been written, and there must not be a request
                        // entity body included with the request.
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          Azure::Core::Nullable<int64_t>
              ContentLength; // Required for "Append Data" and "Flush Data".  Must be 0 for "Flush
                             // Data".  Must be the length of the request content in bytes for
                             // "Append Data".
          Azure::Core::Nullable<std::string>
              TransactionalContentMd5; // Specify the transactional md5 for the body, to be
                                       // validated by the service.
          Azure::Core::Nullable<std::string>
              ContentCrc64; // Specify the transactional crc64 for the body, to be validated by the
                            // service.
          Azure::Core::Nullable<std::string>
              LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease
                               // is active and matches this ID.
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
        };

        static Azure::Core::Response<PathAppendDataResult> AppendData(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::BodyStream& bodyStream,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const AppendDataOptions& appendDataOptions)
        {
          Azure::Core::Http::Request request(
              Azure::Core::Http::HttpMethod::Patch, url, &bodyStream);
          request.GetUrl().AppendQueryParameter(Details::c_QueryAction, "append");
          if (appendDataOptions.Position.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryPosition,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(appendDataOptions.Position.GetValue())));
          }
          if (appendDataOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(appendDataOptions.Timeout.GetValue())));
          }
          if (appendDataOptions.ContentLength.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentLength,
                std::to_string(appendDataOptions.ContentLength.GetValue()));
          }
          if (appendDataOptions.TransactionalContentMd5.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderTransactionalContentMd5,
                appendDataOptions.TransactionalContentMd5.GetValue());
          }
          if (appendDataOptions.ContentCrc64.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderContentCrc64, appendDataOptions.ContentCrc64.GetValue());
          }
          if (appendDataOptions.LeaseIdOptional.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderLeaseIdOptional, appendDataOptions.LeaseIdOptional.GetValue());
          }
          if (appendDataOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, appendDataOptions.ClientRequestId.GetValue());
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, appendDataOptions.ApiVersionParameter);
          return AppendDataParseResult(context, pipeline.Send(context, request));
        }

        struct SetExpiryOptions
        {
          Azure::Core::Nullable<int32_t>
              Timeout; // The timeout parameter is expressed in seconds.
                       // For more information, see <a
                       // href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting
                       // Timeouts for Blob Service Operations.</a>
          std::string ApiVersionParameter
              = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to
                                                     // use for this request.
          Azure::Core::Nullable<std::string>
              ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                               // limit that is recorded in the analytics logs when storage
                               // analytics logging is enabled.
          PathExpiryOptions XMsExpiryOption; // Required. Indicates mode of the expiry time
          Azure::Core::Nullable<std::string> PathExpiryTime; // The time to set the blob to expiry
        };

        static Azure::Core::Response<PathSetExpiryResult> SetExpiry(
            const Azure::Core::Http::Url& url,
            Azure::Core::Http::HttpPipeline& pipeline,
            const Azure::Core::Context& context,
            const SetExpiryOptions& setExpiryOptions)
        {
          Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
          request.AddHeader(Details::c_HeaderContentLength, "0");
          request.GetUrl().AppendQueryParameter(Details::c_QueryComp, "expiry");
          if (setExpiryOptions.Timeout.HasValue())
          {
            request.GetUrl().AppendQueryParameter(
                Details::c_QueryTimeout,
                Storage::Details::UrlEncodeQueryParameter(
                    std::to_string(setExpiryOptions.Timeout.GetValue())));
          }
          request.AddHeader(
              Details::c_HeaderApiVersionParameter, setExpiryOptions.ApiVersionParameter);
          if (setExpiryOptions.ClientRequestId.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderClientRequestId, setExpiryOptions.ClientRequestId.GetValue());
          }
          request.AddHeader(
              Details::c_HeaderPathExpiryOptions,
              PathExpiryOptionsToString(setExpiryOptions.XMsExpiryOption));
          if (setExpiryOptions.PathExpiryTime.HasValue())
          {
            request.AddHeader(
                Details::c_HeaderPathExpiryTime, setExpiryOptions.PathExpiryTime.GetValue());
          }
          return SetExpiryParseResult(context, pipeline.Send(context, request));
        }

      private:
        static Azure::Core::Response<PathCreateResult> CreateParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
          {
            // The file or directory was created.
            PathCreateResult result;
            if (response.GetHeaders().find(Details::c_HeaderETag) != response.GetHeaders().end())
            {
              result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            }
            if (response.GetHeaders().find(Details::c_HeaderLastModified)
                != response.GetHeaders().end())
            {
              result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsContinuation)
                != response.GetHeaders().end())
            {
              result.ContinuationToken = response.GetHeaders().at(Details::c_HeaderXMsContinuation);
            }
            if (response.GetHeaders().find(Details::c_HeaderContentLength)
                != response.GetHeaders().end())
            {
              result.ContentLength
                  = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
            }
            return Azure::Core::Response<PathCreateResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathLeaseResult> LeaseParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // The "renew", "change" or "release" action was successful.
            PathLeaseResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseId)
                != response.GetHeaders().end())
            {
              result.LeaseId = response.GetHeaders().at(Details::c_HeaderXMsLeaseId);
            }
            return Azure::Core::Response<PathLeaseResult>(
                std::move(result), std::move(responsePtr));
          }
          else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
          {
            // A new lease has been created.  The "acquire" action was successful.
            PathLeaseResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseId)
                != response.GetHeaders().end())
            {
              result.LeaseId = response.GetHeaders().at(Details::c_HeaderXMsLeaseId);
            }
            return Azure::Core::Response<PathLeaseResult>(
                std::move(result), std::move(responsePtr));
          }
          else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
          {
            // The "break" lease action was successful.
            PathLeaseResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            result.LeaseTime = response.GetHeaders().at(Details::c_HeaderXMsLeaseTime);
            return Azure::Core::Response<PathLeaseResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathReadResult> ReadParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Ok
            PathReadResult result;
            result.BodyStream = response.GetBodyStream();
            result.AcceptRanges = response.GetHeaders().at(Details::c_HeaderAcceptRanges);
            if (response.GetHeaders().find("cache-control") != response.GetHeaders().end())
            {
              result.HttpHeaders.CacheControl = response.GetHeaders().at("cache-control");
            }
            if (response.GetHeaders().find("content-disposition") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentDisposition
                  = response.GetHeaders().at("content-disposition");
            }
            if (response.GetHeaders().find("content-encoding") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentEncoding = response.GetHeaders().at("content-encoding");
            }
            if (response.GetHeaders().find("content-language") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentLanguage = response.GetHeaders().at("content-language");
            }
            if (response.GetHeaders().find(Details::c_HeaderContentLength)
                != response.GetHeaders().end())
            {
              result.ContentLength
                  = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
            }
            if (response.GetHeaders().find(Details::c_HeaderContentRange)
                != response.GetHeaders().end())
            {
              result.ContentRange = response.GetHeaders().at(Details::c_HeaderContentRange);
            }
            if (response.GetHeaders().find("content-type") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentType = response.GetHeaders().at("content-type");
            }
            if (response.GetHeaders().find(Details::c_HeaderContentMD5)
                != response.GetHeaders().end())
            {
              result.ContentMd5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
            }
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            result.ResourceType = response.GetHeaders().at(Details::c_HeaderXMsResourceType);
            if (response.GetHeaders().find(Details::c_HeaderXMsProperties)
                != response.GetHeaders().end())
            {
              result.Properties = response.GetHeaders().at(Details::c_HeaderXMsProperties);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseDuration)
                != response.GetHeaders().end())
            {
              result.LeaseDuration = response.GetHeaders().at(Details::c_HeaderXMsLeaseDuration);
            }
            result.LeaseState = LeaseStateTypeFromString(
                response.GetHeaders().at(Details::c_HeaderXMsLeaseState));
            result.LeaseStatus = LeaseStatusTypeFromString(
                response.GetHeaders().at(Details::c_HeaderXMsLeaseStatus));
            return Azure::Core::Response<PathReadResult>(std::move(result), std::move(responsePtr));
          }
          else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::PartialContent)
          {
            // Partial content
            PathReadResult result;
            result.BodyStream = response.GetBodyStream();
            result.AcceptRanges = response.GetHeaders().at(Details::c_HeaderAcceptRanges);
            if (response.GetHeaders().find("cache-control") != response.GetHeaders().end())
            {
              result.HttpHeaders.CacheControl = response.GetHeaders().at("cache-control");
            }
            if (response.GetHeaders().find("content-disposition") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentDisposition
                  = response.GetHeaders().at("content-disposition");
            }
            if (response.GetHeaders().find("content-encoding") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentEncoding = response.GetHeaders().at("content-encoding");
            }
            if (response.GetHeaders().find("content-language") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentLanguage = response.GetHeaders().at("content-language");
            }
            if (response.GetHeaders().find(Details::c_HeaderContentLength)
                != response.GetHeaders().end())
            {
              result.ContentLength
                  = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
            }
            if (response.GetHeaders().find(Details::c_HeaderContentRange)
                != response.GetHeaders().end())
            {
              result.ContentRange = response.GetHeaders().at(Details::c_HeaderContentRange);
            }
            if (response.GetHeaders().find("content-type") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentType = response.GetHeaders().at("content-type");
            }
            if (response.GetHeaders().find(Details::c_HeaderContentMD5)
                != response.GetHeaders().end())
            {
              result.TransactionalMd5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsContentMd5)
                != response.GetHeaders().end())
            {
              result.ContentMd5 = response.GetHeaders().at(Details::c_HeaderXMsContentMd5);
            }
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            result.ResourceType = response.GetHeaders().at(Details::c_HeaderXMsResourceType);
            if (response.GetHeaders().find(Details::c_HeaderXMsProperties)
                != response.GetHeaders().end())
            {
              result.Properties = response.GetHeaders().at(Details::c_HeaderXMsProperties);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseDuration)
                != response.GetHeaders().end())
            {
              result.LeaseDuration = response.GetHeaders().at(Details::c_HeaderXMsLeaseDuration);
            }
            result.LeaseState = LeaseStateTypeFromString(
                response.GetHeaders().at(Details::c_HeaderXMsLeaseState));
            result.LeaseStatus = LeaseStatusTypeFromString(
                response.GetHeaders().at(Details::c_HeaderXMsLeaseStatus));
            return Azure::Core::Response<PathReadResult>(std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathGetPropertiesResult> GetPropertiesParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Returns all properties for the file or directory.
            PathGetPropertiesResult result;
            if (response.GetHeaders().find(Details::c_HeaderAcceptRanges)
                != response.GetHeaders().end())
            {
              result.AcceptRanges = response.GetHeaders().at(Details::c_HeaderAcceptRanges);
            }
            if (response.GetHeaders().find("cache-control") != response.GetHeaders().end())
            {
              result.HttpHeaders.CacheControl = response.GetHeaders().at("cache-control");
            }
            if (response.GetHeaders().find("content-disposition") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentDisposition
                  = response.GetHeaders().at("content-disposition");
            }
            if (response.GetHeaders().find("content-encoding") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentEncoding = response.GetHeaders().at("content-encoding");
            }
            if (response.GetHeaders().find("content-language") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentLanguage = response.GetHeaders().at("content-language");
            }
            if (response.GetHeaders().find(Details::c_HeaderContentLength)
                != response.GetHeaders().end())
            {
              result.ContentLength
                  = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
            }
            if (response.GetHeaders().find(Details::c_HeaderContentRange)
                != response.GetHeaders().end())
            {
              result.ContentRange = response.GetHeaders().at(Details::c_HeaderContentRange);
            }
            if (response.GetHeaders().find("content-type") != response.GetHeaders().end())
            {
              result.HttpHeaders.ContentType = response.GetHeaders().at("content-type");
            }
            if (response.GetHeaders().find(Details::c_HeaderContentMD5)
                != response.GetHeaders().end())
            {
              result.ContentMd5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
            }
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            if (response.GetHeaders().find(Details::c_HeaderXMsResourceType)
                != response.GetHeaders().end())
            {
              result.ResourceType = response.GetHeaders().at(Details::c_HeaderXMsResourceType);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsProperties)
                != response.GetHeaders().end())
            {
              result.Properties = response.GetHeaders().at(Details::c_HeaderXMsProperties);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsOwner)
                != response.GetHeaders().end())
            {
              result.Owner = response.GetHeaders().at(Details::c_HeaderXMsOwner);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsGroup)
                != response.GetHeaders().end())
            {
              result.Group = response.GetHeaders().at(Details::c_HeaderXMsGroup);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsPermissions)
                != response.GetHeaders().end())
            {
              result.Permissions = response.GetHeaders().at(Details::c_HeaderXMsPermissions);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsAcl) != response.GetHeaders().end())
            {
              result.Acl = response.GetHeaders().at(Details::c_HeaderXMsAcl);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseDuration)
                != response.GetHeaders().end())
            {
              result.LeaseDuration = response.GetHeaders().at(Details::c_HeaderXMsLeaseDuration);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseState)
                != response.GetHeaders().end())
            {
              result.LeaseState = LeaseStateTypeFromString(
                  response.GetHeaders().at(Details::c_HeaderXMsLeaseState));
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsLeaseStatus)
                != response.GetHeaders().end())
            {
              result.LeaseStatus = LeaseStatusTypeFromString(
                  response.GetHeaders().at(Details::c_HeaderXMsLeaseStatus));
            }
            return Azure::Core::Response<PathGetPropertiesResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathDeleteResult> DeleteParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // The file was deleted.
            PathDeleteResult result;
            if (response.GetHeaders().find(Details::c_HeaderXMsContinuation)
                != response.GetHeaders().end())
            {
              result.ContinuationToken = response.GetHeaders().at(Details::c_HeaderXMsContinuation);
            }
            return Azure::Core::Response<PathDeleteResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathSetAccessControlResult> SetAccessControlParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Set directory access control response.
            PathSetAccessControlResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            return Azure::Core::Response<PathSetAccessControlResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathSetAccessControlRecursiveResult>
        SetAccessControlRecursiveParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // Set directory access control recursive response.
            const auto& bodyBuffer = response.GetBody();
            PathSetAccessControlRecursiveResult result = bodyBuffer.empty()
                ? PathSetAccessControlRecursiveResult()
                : PathSetAccessControlRecursiveResultFromSetAccessControlRecursiveResponse(
                    SetAccessControlRecursiveResponseFromJson(nlohmann::json::parse(bodyBuffer)));
            if (response.GetHeaders().find(Details::c_HeaderXMsContinuation)
                != response.GetHeaders().end())
            {
              result.ContinuationToken = response.GetHeaders().at(Details::c_HeaderXMsContinuation);
            }
            return Azure::Core::Response<PathSetAccessControlRecursiveResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Storage::Files::DataLake::AclFailedEntry AclFailedEntryFromJson(
            const nlohmann::json& node)
        {
          Storage::Files::DataLake::AclFailedEntry result;
          result.Name = node["name"].get<std::string>();
          result.Type = node["type"].get<std::string>();
          result.ErrorMessage = node["errorMessage"].get<std::string>();
          return result;
        }

        static Storage::Files::DataLake::SetAccessControlRecursiveResponse
        SetAccessControlRecursiveResponseFromJson(const nlohmann::json& node)
        {
          Storage::Files::DataLake::SetAccessControlRecursiveResponse result;
          result.DirectoriesSuccessful = node["directoriesSuccessful"].get<int32_t>();
          result.FilesSuccessful = node["filesSuccessful"].get<int32_t>();
          result.FailureCount = node["failureCount"].get<int32_t>();
          for (const auto& element : node["failedEntries"])
          {
            result.FailedEntries.emplace_back(AclFailedEntryFromJson(element));
          }
          return result;
        }

        static PathSetAccessControlRecursiveResult
        PathSetAccessControlRecursiveResultFromSetAccessControlRecursiveResponse(
            SetAccessControlRecursiveResponse object)
        {
          PathSetAccessControlRecursiveResult result;
          result.DirectoriesSuccessful = object.DirectoriesSuccessful;
          result.FilesSuccessful = object.FilesSuccessful;
          result.FailureCount = object.FailureCount;
          result.FailedEntries = std::move(object.FailedEntries);

          return result;
        }
        static Azure::Core::Response<PathFlushDataResult> FlushDataParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // The data was flushed (written) to the file successfully.
            PathFlushDataResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            if (response.GetHeaders().find(Details::c_HeaderContentLength)
                != response.GetHeaders().end())
            {
              result.ContentLength
                  = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
            }
            return Azure::Core::Response<PathFlushDataResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathAppendDataResult> AppendDataParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
          {
            // Append data to file control response.
            PathAppendDataResult result;
            if (response.GetHeaders().find(Details::c_HeaderContentMD5)
                != response.GetHeaders().end())
            {
              result.ContentMD5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
            }
            if (response.GetHeaders().find(Details::c_HeaderXMsContentCrc64)
                != response.GetHeaders().end())
            {
              result.ContentCrc64 = response.GetHeaders().at(Details::c_HeaderXMsContentCrc64);
            }
            result.IsServerEncrypted
                = response.GetHeaders().at(Details::c_HeaderXMsRequestServerEncrypted) == "true";
            return Azure::Core::Response<PathAppendDataResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }

        static Azure::Core::Response<PathSetExpiryResult> SetExpiryParseResult(
            const Azure::Core::Context& context,
            std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
        {
          /* const */ auto& response = *responsePtr;
          if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
          {
            // The blob expiry was set successfully.
            PathSetExpiryResult result;
            result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
            result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
            return Azure::Core::Response<PathSetExpiryResult>(
                std::move(result), std::move(responsePtr));
          }
          else
          {
            unused(context);
            throw Storage::StorageException::CreateFromResponse(std::move(responsePtr));
          }
        }
      };

    }; // class DataLakeRestClient

  } // namespace Details

}}}} // namespace Azure::Storage::Files::DataLake
