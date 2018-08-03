// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCAuthType.h"
#include "BCIdentityProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCIdentityProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
	GENERATED_BODY()

public:
	UBCIdentityProxy(const FObjectInitializer& ObjectInitializer);

	/*
	* Attach the user's Facebook credentials to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - externalId The facebook id of the user
	* Param - authenticationToken The validated token from the Facebook SDK
	*   (that will be further validated when sent to the bC service)
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Facebook identity you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateFacebook().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachFacebookIdentity(ABrainCloudActor *brainCloud, const FString& facebookId, const FString& authenticationToken);

	/*
	* Merge the profile associated with the provided Facebook credentials with the
	* current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - externalId The facebook id of the user
	* Param - authenticationToken The validated token from the Facebook SDK
	*   (that will be further validated when sent to the bC service)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeFacebookIdentity(ABrainCloudActor *brainCloud, const FString& facebookId, const FString& authenticationToken);

	/*
	* Detach the Facebook identity from this profile.
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - externalId The facebook id of the user
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachFacebookIdentity(ABrainCloudActor *brainCloud, const FString& facebookId, bool continueAnon);

	/*
	* Attach a Game Center identity to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Facebook identity you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call this method again.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachGameCenterIdentity(ABrainCloudActor *brainCloud, const FString& gameCenterId);

	/*
	* Merge the profile associated with the specified Game Center identity with the current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeGameCenterIdentity(ABrainCloudActor *brainCloud, const FString& gameCenterId);


	/*
	* Detach the Game Center identity from the current profile.
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachGameCenterIdentity(ABrainCloudActor *brainCloud, const FString& gameCenterId, bool continueAnon);

	/*
	* Attach a Email and Password identity to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - email The player's e-mail address
	* Param - password The player's password
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and then call AuthenticateEmailPassword().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachEmailIdentity(ABrainCloudActor *brainCloud, const FString& email, const FString& password);

	/*
	* Merge the profile associated with the provided e=mail with the current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - email The user's e-mail address
	* Param - password The user's password
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeEmailIdentity(ABrainCloudActor *brainCloud, const FString& email, const FString& password);

	/*
	* Detach the e-mail identity from the current profile
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - email The user's e-mail address
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachEmailIdentity(ABrainCloudActor *brainCloud, const FString& email, bool continueAnon);

	/*
	* Attach a Universal (userId + password) identity to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - userId The user's userId
	* Param - password The user's password
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and then call AuthenticateEmailPassword().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachUniversalIdentity(ABrainCloudActor *brainCloud, const FString& userId, const FString& password);

	/*
	* Merge the profile associated with the provided e=mail with the current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - userId The user's userId
	* Param - password The user's password
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeUniversalIdentity(ABrainCloudActor *brainCloud, const FString& userId, const FString& password);

	/*
	* Detach the universal identity from the current profile
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - userId The user's userId
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachUniversalIdentity(ABrainCloudActor *brainCloud, const FString& userId, bool continueAnon);

	/*
	* Attach a Steam (userid + steamsessionticket) identity to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - steamId String representation of 64 bit steam id
	* Param - sessionTicket The user's session ticket (hex encoded)
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and then call AuthenticateSteam().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachSteamIdentity(ABrainCloudActor *brainCloud, const FString& steamId, const FString& sessionTicket);

	/*
	* Merge the profile associated with the provided steam userid with the current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - steamId String representation of 64 bit steam id
	* Param - sessionTicket The user's session ticket (hex encoded)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeSteamIdentity(ABrainCloudActor *brainCloud, const FString& steamId, const FString& sessionTicket);

	/*
	* Detach the steam identity from the current profile
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - steamId String representation of 64 bit steam id
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachSteamIdentity(ABrainCloudActor *brainCloud, const FString& steamId, bool continueAnon);

	/**
	* Attach the user's Google credentials to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - googleId The Google id of the user
	* Param - authenticationToken The validated token from the Google SDK
	*   (that will be further validated when sent to the bC service)
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateGoogle().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachGoogleIdentity(ABrainCloudActor *brainCloud, const FString& googleId, const FString& authenticationToken);

	/**
	* Merge the profile associated with the provided Google credentials with the
	* current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - externalId The Google id of the user
	* Param - authenticationToken The validated token from the Google SDK
	*   (that will be further validated when sent to the bC service)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeGoogleIdentity(ABrainCloudActor *brainCloud, const FString& googleId, const FString& authenticationToken);

	/*
	* Detach the Google identity from this profile.
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - googleId The Google id of the user
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachGoogleIdentity(ABrainCloudActor *brainCloud, const FString& googleId, bool continueAnon);

	/**
	* Attach the user's Twitter credentials to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - twitterId The Twitter id of the user
	* Param - authenticationToken The authentication token derrived from the twitter APIs
	* Param - secret The secret given when attempting to link with Twitter
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Twitter identity you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateTwitter().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachTwitterIdentity(ABrainCloudActor *brainCloud, const FString& twitterId, const FString& authenticationToken, const FString& secret);

	/**
	* Merge the profile associated with the provided Twitter credentials with the
	* current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - twitterId The Twitter id of the user
	* Param - authenticationToken The authentication token derrived from the twitter APIs
	* Param - secret The secret given when attempting to link with Twitter
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeTwitterIdentity(ABrainCloudActor *brainCloud, const FString& twitterId, const FString& authenticationToken, const FString& secret);

	/**
	* Detach the Twitter identity from this profile.
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - twitterId The Twitter id of the user
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachTwitterIdentity(ABrainCloudActor *brainCloud, const FString& twitterId, bool continueAnon);

	/**
	* Attach the user's Parse credentials to the current profile.
	*
	* Service Name - identity
	* Service Operation - Attach
	*
	* Param - parseId The Parse id of the user
	* Param - authenticationToken The validated token from Parse
	*   (that will be further validated when sent to the bC service)
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Parse identity you provided
	* already points to a different profile.  You will likely want to offer the user the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateParse().
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* AttachParseIdentity(ABrainCloudActor *brainCloud, const FString& parseId, const FString& authenticationToken);

	/**
	* Merge the profile associated with the provided Parse credentials with the
	* current profile.
	*
	* Service Name - identity
	* Service Operation - Merge
	*
	* Param - externalId The Parse id of the user
	* Param - authenticationToken The validated token from Parse
	*   (that will be further validated when sent to the bC service)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* MergeParseIdentity(ABrainCloudActor *brainCloud, const FString& parseId, const FString& authenticationToken);

	/*
	* Detach the Parse identity from this profile.
	*
	* Service Name - identity
	* Service Operation - Detach
	*
	* Param - parseId The Parse id of the user
	* Param - continueAnon Proceed even if the profile will revert to anonymous?
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* DetachParseIdentity(ABrainCloudActor *brainCloud, const FString& parseId, bool continueAnon);

	/**
	* Switch to a Child Profile
	*
	* Service Name - identity
	* Service Operation - SWITCH_TO_CHILD_PROFILE
	*
	* Param - childProfileId The profileId of the child profile to switch to
	* If null and forceCreate is true a new profile will be created
	* Param - childAppId The appId of the child app to switch to
	* Param - forceCreate Should a new profile be created if it does not exist?
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* SwitchToChildProfile(ABrainCloudActor *brainCloud, const FString& childProfileId, const FString& childAppId, bool forceCreate);

	/**
	* Switches to a child profile of an app when only one profile exists
	* If multiple profiles exist this returns an error
	*
	* Service Name - identity
	* Service Operation - SWITCH_TO_CHILD_PROFILE
	*
	* Param - childAppId The App ID of the child app to switch to
	* Param - forceCreate Should a new profile be created if it does not exist?
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* SwitchToSingletonChildProfile(ABrainCloudActor *brainCloud, const FString& childAppId, bool forceCreate);

	/**
	* Switch to a Parent Profile
	*
	* Service Name - identity
	* Service Operation - SWITCH_TO_PARENT_PROFILE
	*
	* Param - parentLevelName The level of the parent to switch to
	* If null and forceCreate is true a new profile will be created
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* SwitchToParentProfile(ABrainCloudActor *brainCloud, const FString& parentLevelName);

	/**
	* Returns a list of all child profiles in child Apps
	*
	* Service Name - identity
	* Service Operation - GET_CHILD_PROFILES
	*
	* Param - includeSummaryData Whether to return the summary friend data along with this call
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* GetChildProfiles(ABrainCloudActor *brainCloud, bool includeSummaryData);

	/**
	* Retrieve list of identities
	*
	* Service Name - identity
	* Service Operation - GET_IDENTITIES
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* GetIdentities(ABrainCloudActor *brainCloud);

	/**
	* Retrieve list of expired identities
	*
	* Service Name - identity
	* Service Operation - GET_EXPIRED_IDENTITIES
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* GetExpiredIdentities(ABrainCloudActor *brainCloud);

	/**
	* Refreshes an identity for this user
	*
	* Service Name - identity
	* Service Operation - REFRESH_IDENTITY
	*
	* Param - externalId User ID
	* Param - authenticationToken Password or client side token
	* Param - authenticationType Type of authentication
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* RefreshIdentity(ABrainCloudActor *brainCloud, const FString& externalId, const FString& authenticationToken, EBCAuthType authenticationType);

	 /**
     * Allows email identity email address to be changed
     *
     * Service Name - identity
     * Service Operation - CHANGE_EMAIL_IDENTITY
     *
     * Param - oldEmailAddress Old email address
     * Param - password Password for identity
     * Param - newEmailAddress New email address
     * Param - updateContactEmail Whether to update contact email in profile
     */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy* ChangeEmailIdentity(ABrainCloudActor *brainCloud, const FString& oldEmailAddress, const FString& password, const FString& newEmailAddress, bool updateContactEmail);


	/**
	* Attach a new identity to a parent app
	*
	* Service Name - identity
	* Service Operation - ATTACH_PARENT_WITH_IDENTITY
	*
	* Param - externalId The users id for the new credentials
	* Param - authenticationToken The password/token
	* Param - authenticationType Type of identity
	* Param - externalAuthName Optional - if attaching an external identity
	* Param - forceCreate Should a new profile be created if it does not exist?
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy*  AttachParentWithIdentity(ABrainCloudActor *brainCloud, const FString& externalId, const FString& authenticationToken,
			EBCAuthType authenticationType, const FString& externalAuthName, bool forceCreate);

	/**
	* Detaches parent from this user's profile
	*
	* Service Name - identity
	* Service Operation - DETACH_PARENT
	*
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy*  DetachParent(ABrainCloudActor *brainCloud);

	/**
	* Attaches a peer identity to this user's profile
	*
	* Service Name - identity
	* Service Operation - ATTACH_PEER_PROFILE
	*
	* Param - peer Name of the peer to connect to
	* Param - externalId The users id for the new credentials
	* Param - authenticationToken The password/token
	* Param - authenticationType Type of identity
	* Param - externalAuthName Optional - if attaching an external identity
	* Param - forceCreate Should a new profile be created if it does not exist?
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy*  AttachPeerProfile(ABrainCloudActor *brainCloud, const FString& peer, const FString& externalId, const FString& authenticationToken, EBCAuthType authenticationType,
			const FString& externalAuthName, bool forceCreate);

	/**
	* Detaches a peer identity from this user's profile
	*
	* Service Name - identity
	* Service Operation - DETACH_PEER
	*
	* Param - peer Name of the peer to connect to
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy*  DetachPeer(ABrainCloudActor *brainCloud, const FString& peer);

	/**
	* Returns a list of peer profiles attached to this user
	*
	* Service Name - identity
	* Service Operation - GET_PEER_PROFILES
	*
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Identity")
		static UBCIdentityProxy*  GetPeerProfiles(ABrainCloudActor *brainCloud);

	//Response delegates
	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnFailure;

protected:
	// IServerCallback interface
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
	// End of IServerCallback interface
};
