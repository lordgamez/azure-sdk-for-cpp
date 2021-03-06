// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "datalake_path_client_test.hpp"

#include <algorithm>

namespace Azure { namespace Storage { namespace Test {

  std::shared_ptr<Files::DataLake::PathClient> DataLakePathClientTest::m_pathClient;
  std::string DataLakePathClientTest::m_pathName;

  void DataLakePathClientTest::SetUpTestSuite()
  {
    DataLakeFileSystemClientTest::SetUpTestSuite();
    m_pathName = LowercaseRandomString(10);
    m_pathClient = std::make_shared<Files::DataLake::PathClient>(
        m_fileSystemClient->GetPathClient(m_pathName));
    m_fileSystemClient->GetFileClient(m_pathName).Create();
  }

  void DataLakePathClientTest::TearDownTestSuite()
  {
    m_fileSystemClient->GetFileClient(m_pathName).Delete();
    DataLakeFileSystemClientTest::TearDownTestSuite();
  }

  std::vector<Files::DataLake::Acl> DataLakePathClientTest::GetValidAcls()
  {
    static std::vector<Files::DataLake::Acl> result = []() {
      std::vector<Files::DataLake::Acl> ret;
      Files::DataLake::Acl acl1;
      acl1.Type = "user";
      acl1.Id = "72a3f86f-271f-439e-b031-25678907d381";
      acl1.Permissions = "rwx";
      Files::DataLake::Acl acl2;
      acl2.Type = "user";
      acl2.Id = "";
      acl2.Permissions = "rwx";
      Files::DataLake::Acl acl3;
      acl3.Type = "group";
      acl3.Id = "";
      acl3.Permissions = "r--";
      Files::DataLake::Acl acl4;
      acl4.Type = "other";
      acl4.Id = "";
      acl4.Permissions = "---";
      ret.emplace_back(std::move(acl1));
      ret.emplace_back(std::move(acl2));
      ret.emplace_back(std::move(acl3));
      ret.emplace_back(std::move(acl4));
      return ret;
    }();
    return result;
  }

  TEST_F(DataLakePathClientTest, PathMetadata)
  {
    auto metadata1 = RandomMetadata();
    auto metadata2 = RandomMetadata();
    {
      // Set/Get Metadata works
      EXPECT_NO_THROW(m_pathClient->SetMetadata(metadata1));
      auto result = m_pathClient->GetProperties()->Metadata;
      EXPECT_EQ(metadata1, result);
      EXPECT_NO_THROW(m_pathClient->SetMetadata(metadata2));
      result = m_pathClient->GetProperties()->Metadata;
      EXPECT_EQ(metadata2, result);
    }

    {
      // Create path with metadata works
      auto client1 = m_fileSystemClient->GetFileClient(LowercaseRandomString());
      auto client2 = m_fileSystemClient->GetFileClient(LowercaseRandomString());
      Files::DataLake::CreatePathOptions options1;
      Files::DataLake::CreatePathOptions options2;
      options1.Metadata = metadata1;
      options2.Metadata = metadata2;

      EXPECT_NO_THROW(client1.Create(options1));
      EXPECT_NO_THROW(client2.Create(options2));
      auto result = client1.GetProperties()->Metadata;
      EXPECT_EQ(metadata1, result);
      result = client2.GetProperties()->Metadata;
      EXPECT_EQ(metadata2, result);
    }
  }

  TEST_F(DataLakePathClientTest, GetPathPropertiesResult)
  {
    auto metadata1 = RandomMetadata();
    auto metadata2 = RandomMetadata();
    {
      // Get Metadata via properties works
      EXPECT_NO_THROW(m_pathClient->SetMetadata(metadata1));
      auto result = m_pathClient->GetProperties();
      EXPECT_EQ(metadata1, result->Metadata);
      EXPECT_NO_THROW(m_pathClient->SetMetadata(metadata2));
      result = m_pathClient->GetProperties();
      EXPECT_EQ(metadata2, result->Metadata);
    }

    {
      // Last modified Etag works.
      auto properties1 = m_pathClient->GetProperties();
      auto properties2 = m_pathClient->GetProperties();
      EXPECT_EQ(properties1->ETag, properties2->ETag);
      EXPECT_EQ(properties1->LastModified, properties2->LastModified);

      // This operation changes ETag/LastModified.
      EXPECT_NO_THROW(m_pathClient->SetMetadata(metadata1));

      auto properties3 = m_pathClient->GetProperties();
      EXPECT_NE(properties1->ETag, properties3->ETag);
    }
  }

  TEST_F(DataLakePathClientTest, PathHttpHeaders)
  {
    {
      // Http headers works with create.
      auto httpHeader = GetInterestingHttpHeaders();
      std::vector<Files::DataLake::PathClient> pathClient;
      for (int32_t i = 0; i < 2; ++i)
      {
        auto client = m_fileSystemClient->GetFileClient(LowercaseRandomString());
        Files::DataLake::CreatePathOptions options;
        options.HttpHeaders = httpHeader;
        EXPECT_NO_THROW(client.Create(options));
        pathClient.emplace_back(std::move(client));
      }
      for (const auto& client : pathClient)
      {
        auto result = client.GetProperties();
        EXPECT_EQ(httpHeader.CacheControl, result->HttpHeaders.CacheControl);
        EXPECT_EQ(httpHeader.ContentDisposition, result->HttpHeaders.ContentDisposition);
        EXPECT_EQ(httpHeader.ContentLanguage, result->HttpHeaders.ContentLanguage);
        EXPECT_EQ(httpHeader.ContentType, result->HttpHeaders.ContentType);
      }
    }

    {
      // Http headers works with SetHttpHeaders.
      auto httpHeader = GetInterestingHttpHeaders();
      std::vector<Files::DataLake::PathClient> pathClient;
      for (int32_t i = 0; i < 2; ++i)
      {
        auto client = m_fileSystemClient->GetFileClient(LowercaseRandomString());
        EXPECT_NO_THROW(client.Create());
        EXPECT_NO_THROW(client.SetHttpHeaders(httpHeader));
        pathClient.emplace_back(std::move(client));
      }
      for (const auto& client : pathClient)
      {
        auto result = client.GetProperties();
        EXPECT_EQ(httpHeader.CacheControl, result->HttpHeaders.CacheControl);
        EXPECT_EQ(httpHeader.ContentDisposition, result->HttpHeaders.ContentDisposition);
        EXPECT_EQ(httpHeader.ContentLanguage, result->HttpHeaders.ContentLanguage);
        EXPECT_EQ(httpHeader.ContentType, result->HttpHeaders.ContentType);
      }
    }

    {
      // Set http headers work with last modified access condition.
      auto response = m_pathClient->GetProperties();
      Files::DataLake::SetPathHttpHeadersOptions options1;
      options1.AccessConditions.IfModifiedSince = response->LastModified;
      EXPECT_THROW(
          m_pathClient->SetHttpHeaders(GetInterestingHttpHeaders(), options1), StorageException);
      Files::DataLake::SetPathHttpHeadersOptions options2;
      options2.AccessConditions.IfUnmodifiedSince = response->LastModified;
      EXPECT_NO_THROW(m_pathClient->SetHttpHeaders(GetInterestingHttpHeaders(), options2));
    }

    {
      // Set http headers work with last modified access condition.
      auto response = m_pathClient->GetProperties();
      Files::DataLake::SetPathHttpHeadersOptions options1;
      options1.AccessConditions.IfNoneMatch = response->ETag;
      EXPECT_THROW(
          m_pathClient->SetHttpHeaders(GetInterestingHttpHeaders(), options1), StorageException);
      Files::DataLake::SetPathHttpHeadersOptions options2;
      options2.AccessConditions.IfMatch = response->ETag;
      EXPECT_NO_THROW(m_pathClient->SetHttpHeaders(GetInterestingHttpHeaders(), options2));
    }
  }

  TEST_F(DataLakePathClientTest, PathAccessControls)
  {
    {
      // Set/Get Acls works.
      std::vector<Files::DataLake::Acl> acls = GetValidAcls();
      EXPECT_NO_THROW(m_pathClient->SetAccessControl(acls));
      std::vector<Files::DataLake::Acl> resultAcls;
      EXPECT_NO_THROW(resultAcls = m_pathClient->GetAccessControls()->Acls);
      EXPECT_EQ(resultAcls.size(), acls.size() + 1); // Always append mask::rwx
      for (const auto& acl : acls)
      {
        auto iter = std::find_if(
            resultAcls.begin(), resultAcls.end(), [&acl](const Files::DataLake::Acl& targetAcl) {
              return (targetAcl.Type == acl.Type) && (targetAcl.Id == acl.Id)
                  && (targetAcl.Scope == acl.Scope);
            });
        EXPECT_TRUE(iter != resultAcls.end());
        EXPECT_EQ(iter->Permissions, acl.Permissions);
      }
    }

    {
      // Set/Get Acls works with last modified access condition.
      std::vector<Files::DataLake::Acl> acls = GetValidAcls();

      auto response = m_pathClient->GetProperties();
      Files::DataLake::SetPathAccessControlOptions options1;
      options1.AccessConditions.IfModifiedSince = response->LastModified;
      EXPECT_THROW(m_pathClient->SetAccessControl(acls, options1), StorageException);
      Files::DataLake::SetPathAccessControlOptions options2;
      options2.AccessConditions.IfUnmodifiedSince = response->LastModified;
      EXPECT_NO_THROW(m_pathClient->SetAccessControl(acls, options2));
    }

    {
      // Set/Get Acls works with if match access condition.
      std::vector<Files::DataLake::Acl> acls = GetValidAcls();
      auto response = m_pathClient->GetProperties();
      Files::DataLake::SetPathAccessControlOptions options1;
      options1.AccessConditions.IfNoneMatch = response->ETag;
      EXPECT_THROW(m_pathClient->SetAccessControl(acls, options1), StorageException);
      Files::DataLake::SetPathAccessControlOptions options2;
      options2.AccessConditions.IfMatch = response->ETag;
      EXPECT_NO_THROW(m_pathClient->SetAccessControl(acls, options2));
    }
  }

  TEST_F(DataLakePathClientTest, LeaseRelated)
  {
    std::string leaseId1 = CreateUniqueLeaseId();
    int32_t leaseDuration = 20;
    auto aLease = *m_pathClient->AcquireLease(leaseId1, leaseDuration);
    EXPECT_FALSE(aLease.ETag.empty());
    EXPECT_FALSE(aLease.LastModified.empty());
    EXPECT_EQ(aLease.LeaseId, leaseId1);
    aLease = *m_pathClient->AcquireLease(leaseId1, leaseDuration);
    EXPECT_FALSE(aLease.ETag.empty());
    EXPECT_FALSE(aLease.LastModified.empty());
    EXPECT_EQ(aLease.LeaseId, leaseId1);

    auto properties = *m_pathClient->GetProperties();
    EXPECT_EQ(properties.LeaseState.GetValue(), Files::DataLake::LeaseStateType::Leased);
    EXPECT_EQ(properties.LeaseStatus.GetValue(), Files::DataLake::LeaseStatusType::Locked);
    EXPECT_FALSE(properties.LeaseDuration.GetValue().empty());

    auto rLease = *m_pathClient->RenewLease(leaseId1);
    EXPECT_FALSE(rLease.ETag.empty());
    EXPECT_FALSE(rLease.LastModified.empty());
    EXPECT_EQ(rLease.LeaseId, leaseId1);

    std::string leaseId2 = CreateUniqueLeaseId();
    EXPECT_NE(leaseId1, leaseId2);
    auto cLease = *m_pathClient->ChangeLease(leaseId1, leaseId2);
    EXPECT_FALSE(cLease.ETag.empty());
    EXPECT_FALSE(cLease.LastModified.empty());
    EXPECT_EQ(cLease.LeaseId, leaseId2);

    auto pathInfo = *m_pathClient->ReleaseLease(leaseId2);
    EXPECT_FALSE(pathInfo.ETag.empty());
    EXPECT_FALSE(pathInfo.LastModified.empty());

    aLease = *m_pathClient->AcquireLease(CreateUniqueLeaseId(), c_InfiniteLeaseDuration);
    properties = *m_pathClient->GetProperties();
    EXPECT_FALSE(properties.LeaseDuration.GetValue().empty());
    auto brokenLease = *m_pathClient->BreakLease();
    EXPECT_FALSE(brokenLease.ETag.empty());
    EXPECT_FALSE(brokenLease.LastModified.empty());
    EXPECT_EQ(brokenLease.LeaseTime, 0);

    aLease = *m_pathClient->AcquireLease(CreateUniqueLeaseId(), leaseDuration);
    Files::DataLake::BreakPathLeaseOptions breakOptions;
    breakOptions.BreakPeriod = 30;
    brokenLease = *m_pathClient->BreakLease(breakOptions);
    EXPECT_FALSE(brokenLease.ETag.empty());
    EXPECT_FALSE(brokenLease.LastModified.empty());
    EXPECT_NE(brokenLease.LeaseTime, 0);

    Files::DataLake::BreakPathLeaseOptions options;
    options.BreakPeriod = 0;
    m_pathClient->BreakLease(options);
  }
}}} // namespace Azure::Storage::Test
