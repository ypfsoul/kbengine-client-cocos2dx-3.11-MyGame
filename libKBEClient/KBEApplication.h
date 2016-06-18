//
//  KNetworkInterface.h
//  libKBEClient
//
//  Created by Tom on 6/12/14.
//  Copyright (c) 2014 Tom. All rights reserved.
//

#ifndef __libKBEClient__KBECCNetworkInterface__
#define __libKBEClient__KBECCNetworkInterface__

#include "KBEClientcore.h"
#include "KClient_interface_marcos.h"
#include <unordered_map>
#include "KDataTypes.h"
#include "KEntity.h"
#include "KMailbox.h"
#include "KEntitydef.h"
#include "KMemoryStream.h"


namespace KBEngineClient
{
	void KBE_init();	
	void KBE_run();
	typedef	std::unordered_map<std::string,std::string>	SPACE_DATA;
	typedef int8 CLIENT_CTYPE;
	/**
	���������� ��Ҫ�Ƿ��������ظ��ͻ����õġ�
*/
	
typedef uint16 SERVER_ERROR_CODE;								// ���������


#define SERVER_SUCCESS								0			// �ɹ���
#define SERVER_ERR_SRV_NO_READY						1			// ������û��׼���á�
#define SERVER_ERR_SRV_OVERLOAD						2			// ���������ع��ء�
#define SERVER_ERR_ILLEGAL_LOGIN					3			// �Ƿ���¼��
#define SERVER_ERR_NAME_PASSWORD					4			// �û����������벻��ȷ��
#define SERVER_ERR_NAME								5			// �û�������ȷ��
#define SERVER_ERR_PASSWORD							6			// ���벻��ȷ��
#define SERVER_ERR_ACCOUNT_CREATE					7			// �����˺�ʧ�ܣ��Ѿ�����һ����ͬ���˺ţ���
#define SERVER_ERR_BUSY								8			// �������ڷ�æ(���磺�ڷ�����ǰһ������δִ����ϵ����������N�δ����˺�)��
#define SERVER_ERR_ANOTHER_LOGON					9			// ��ǰ�˺�����һ����¼�ˡ�
#define SERVER_ERR_ACCOUNT_ONLINE					10			// ���Ѿ���¼�ˣ� �������ܾ��ٴε�¼��
#define SERVER_ERR_PROXY_DESTROYED					11			// ��ͻ��˹�����proxy�ڷ��������Ѿ����١�
#define SERVER_ERR_DIGEST							12			// defmd5��ƥ�䡣
#define SERVER_ERR_SHUTTINGDOWN						13			// ���������ڹر���
#define SERVER_ERR_NAME_MAIL						14			// email��ַ����
#define SERVER_ERR_ACCOUNT_LOCK						15			// �˺ű����ᡣ
#define SERVER_ERR_ACCOUNT_DEADLINE					16			// �˺��ѹ��ڡ�
#define SERVER_ERR_ACCOUNT_NOT_ACTIVATED			17			// �˺�δ���
#define SERVER_ERR_VERSION_NOT_MATCH				18			// �˺�δ���
#define SERVER_ERR_FAILED							19			// ����ʧ�ܡ�

const char SERVER_ERR_STR[][256] = {
	"SERVER_SUCCESS",
	"SERVER_ERR_SRV_NO_READY",
	"SERVER_ERR_SRV_OVERLOAD",
	"SERVER_ERR_ILLEGAL_LOGIN",
	"SERVER_ERR_NAME_PASSWORD",
	"SERVER_ERR_NAME",
	"SERVER_ERR_PASSWORD",
	"SERVER_ERR_ACCOUNT_CREATE",
	"SERVER_ERR_BUSY",
	"SERVER_ERR_ANOTHER_LOGON",
	"SERVER_ERR_ACCOUNT_ONLINE",
	"SERVER_ERR_PROXY_DESTROYED",
	"SERVER_ERR_DIGEST",
	"SERVER_ERR_SHUTTINGDOWN",
	"SERVER_ERR_NAME_MAIL",
	"SERVER_ERR_ACCOUNT_LOCK",
	"SERVER_ERR_ACCOUNT_DEADLINE",
	"SERVER_ERR_ACCOUNT_NOT_ACTIVATED",
	"SERVER_ERR_VERSION_NOT_MATCH",
	"SERVER_ERR_FAILED"
};

#define KBE_PI									3.1415926535898

	
#define ENTITIES_MAP  std::map<ENTITY_ID,KBEngineClient::Entity*>

	class ClientObjectBase
	{
		public:
			ClientObjectBase(){	 pServerChannel_ = new KNetworkInterface(); pEntities_ = &entities; }
			~ClientObjectBase();
			//Entities<client::Entity>* pEntities()const{ return pEntities_; }
			std::map<ENTITY_ID,Entity*> entities;
			/**
			����һ��entity 
			*/
		
			KBEngineClient::Entity* createEntityCommon(const char* entityType, void* params,
				bool isInitializeScript = true, ENTITY_ID eid = 0, bool initProperty = true, MailBox* base = NULL, MailBox* cell = NULL);
	
			/**
			ͨ��entityID����һ��entity 
				*/
			virtual bool destroyEntity(ENTITY_ID entityID, bool callScript){ return false ;};
			bool createAccount();
			bool login();
			bool loginGateWay();  
			const char* name(){ return name_.c_str(); }
			ENTITY_ID entityID(){ return entityID_; }
			DBID dbid(){ return dbid_; }

			//bool registerEventHandle(EventHandle* pEventHandle);
			//bool deregisterEventHandle(EventHandle* pEventHandle);
	
			//void fireEvent(const EventData* pEventData);
			//EventHandler& eventHandler(){ return eventHandler_; }
		
		/**
			���entitiessizeС��256
			ͨ������λ������ȡentityID
			����ֱ��ȡID
			*/
		
			ENTITY_ID readEntityIDFromStream(MemoryStream& s);

			/**
				��mailbox�����Ի�ȡһ��channel��ʵ��
			*/
			//virtual Mercury::Channel* findChannelByMailbox(EntityMailbox& mailbox);

			/** ����ӿ�
				�ͻ��������˵�һ�ν�������, ����˷���
			*/
			virtual void onHelloCB_(const std::string& verInfo,COMPONENT_TYPE componentType);

			virtual void onHelloCB(MemoryStream& s);

			/** ����ӿ�
				�ͷ���˵İ汾��ƥ��
			*/
			virtual void onVersionNotMatch(MemoryStream& s);
	

			/** ����ӿ�
				�����˺ųɹ���ʧ�ܻص�
			   @failedcode: ʧ�ܷ����� MERCURY_ERR_SRV_NO_READY:������û��׼����, 
											MERCURY_ERR_ACCOUNT_CREATE:����ʧ�ܣ��Ѿ����ڣ�, 
											MERCURY_SUCCESS:�˺Ŵ����ɹ�

											SERVER_ERROR_CODE failedcode;
				@�����Ƹ�������:�����ƶ�������: uint32���� + bytearray
			*/
			virtual void onCreateAccountResult(MemoryStream& s);

			/** ����ӿ�
			   ��¼ʧ�ܻص�
			   @failedcode: ʧ�ܷ����� MERCURY_ERR_SRV_NO_READY:������û��׼����, 
											MERCURY_ERR_SRV_OVERLOAD:���������ع���, 
											MERCURY_ERR_NAME_PASSWORD:�û����������벻��ȷ
			*/
			virtual void onLoginFailed(MemoryStream& s);

			/** ����ӿ�
			   ��¼�ɹ�
			   @ip: ������ip��ַ
			   @port: �������˿�
			*/
			virtual void onLoginSuccessfully(MemoryStream& s);

			/** ����ӿ�
			   ��¼ʧ�ܻص�
			   @failedcode: ʧ�ܷ����� MERCURY_ERR_SRV_NO_READY:������û��׼����, 
											MERCURY_ERR_ILLEGAL_LOGIN:�Ƿ���¼, 
											MERCURY_ERR_NAME_PASSWORD:�û����������벻��ȷ
			*/
			virtual void onLoginGatewayFailed(SERVER_ERROR_CODE failedcode);

			/** ����ӿ�
				���������Ѿ�������һ����ͻ��˹����Ĵ���Entity
			   �ڵ�¼ʱҲ�ɱ��ɹ��ص�
			   @datas: �˺�entity����Ϣ
			*/
			virtual void onCreatedProxies(uint64 rndUUID, ENTITY_ID eid, std::string& entityType);

			/** ����ӿ�
				�������ϵ�entity�Ѿ�������Ϸ������
			*/
			virtual void onEntityEnterWorld(MemoryStream& s);

			/** ����ӿ�
				�������ϵ�entity�Ѿ��뿪��Ϸ������
			*/
			virtual void onEntityLeaveWorld( ENTITY_ID eid);
			virtual void onEntityLeaveWorldOptimized( MemoryStream& s);

			/** ����ӿ�
				���߿ͻ���ĳ��entity�����ˣ� ����entityͨ���ǻ�δonEntityEnterWorld
			*/
			virtual void onEntityDestroyed( ENTITY_ID eid);

			/** ����ӿ�
				�������ϵ�entity�Ѿ�����space��
			*/
			virtual void onEntityEnterSpace( SPACE_ID spaceID, ENTITY_ID eid);

			/** ����ӿ�
				�������ϵ�entity�Ѿ��뿪space��
			*/
			virtual void onEntityLeaveSpace( SPACE_ID spaceID, ENTITY_ID eid);

			/** ����ӿ�
				Զ�̵���entity�ķ��� 
			*/
			virtual void onRemoteMethodCall(MemoryStream& s);
			virtual void onRemoteMethodCallOptimized(MemoryStream& s);
			void onRemoteMethodCall_(ENTITY_ID eid, MemoryStream& s);

			/** ����ӿ�
			   ���߳�������
			*/
			virtual void onKicked(SERVER_ERROR_CODE failedcode) {};

			/** ����ӿ�
				����������entity����
			*/
			virtual void onUpdatePropertys( MemoryStream& s);
			virtual void onUpdatePropertysOptimized( MemoryStream& s);
			void onUpdatePropertys_(ENTITY_ID eid, MemoryStream& s);

			/** ����ӿ�
				������ǿ������entity��λ���볯��
			*/
			virtual void onSetEntityPosAndDir( MemoryStream& s);

			/** ����ӿ�
				����������avatar����λ��
			*/
			virtual void onUpdateBasePos( MemoryStream& s);
			virtual void onUpdateBasePosXZ( MemoryStream& s);

			/** ����ӿ�
				����������VolatileData
			*/
			virtual void onUpdateData( MemoryStream& s);

			virtual void onUpdateData_ypr( MemoryStream& s);
			virtual void onUpdateData_yp( MemoryStream& s);
			virtual void onUpdateData_yr(MemoryStream& s);
			virtual void onUpdateData_pr( MemoryStream& s);
			virtual void onUpdateData_y( MemoryStream& s);
			virtual void onUpdateData_p( MemoryStream& s);
			virtual void onUpdateData_r( MemoryStream& s);

			virtual void onUpdateData_xz( MemoryStream& s);
			virtual void onUpdateData_xz_ypr( MemoryStream& s);
			virtual void onUpdateData_xz_yp( MemoryStream& s);
			virtual void onUpdateData_xz_yr( MemoryStream& s);
			virtual void onUpdateData_xz_pr( MemoryStream& s);
			virtual void onUpdateData_xz_y( MemoryStream& s);
			virtual void onUpdateData_xz_p( MemoryStream& s);
			virtual void onUpdateData_xz_r( MemoryStream& s);

			virtual void onUpdateData_xyz( MemoryStream& s);
			virtual void onUpdateData_xyz_ypr( MemoryStream& s);
			virtual void onUpdateData_xyz_yp( MemoryStream& s);
			virtual void onUpdateData_xyz_yr( MemoryStream& s);
			virtual void onUpdateData_xyz_pr( MemoryStream& s);
			virtual void onUpdateData_xyz_y( MemoryStream& s);
			virtual void onUpdateData_xyz_p( MemoryStream& s);
			virtual void onUpdateData_xyz_r( MemoryStream& s);
	
			void _updateVolatileData(ENTITY_ID entityID, float x, float y, float z, float roll, float pitch, float yaw);

			/** 
				������ҵ������ 
			*/
			virtual void updatePlayerToServer();

			/** ����ӿ�
				download stream��ʼ�� 
			*/
			virtual void onStreamDataStarted(int16 id, uint32 datasize, std::string& descr);

			/** ����ӿ�
				���յ�streamData
			*/
			virtual void onStreamDataRecv( MemoryStream& s);

			/** ����ӿ�
				download stream����� 
			*/
			virtual void onStreamDataCompleted(int16 id);

			/** ����ӿ�
				���յ�ClientMessages(ͨ����web�ȲŻ�Ӧ�õ�)
			*/
			virtual void onImportClientMessages( MemoryStream& s){}

			/** ����ӿ�
				���յ�entitydef(ͨ����web�ȲŻ�Ӧ�õ�)
			*/
			virtual void onImportClientEntityDef(MemoryStream& s){}
	
			/** ����ӿ�
				��������������(ͨ����web�ȲŻ�Ӧ�õ�)
			*/
			virtual void onImportMercuryErrorsDescr(MemoryStream& s){}

			/** ����ӿ�
				�����˺��������󷵻�
			*/
			virtual void onReqAccountResetPasswordCB(SERVER_ERROR_CODE failedcode){}

			/** ����ӿ�
				��������䷵��
			*/
			virtual void onReqAccountBindEmailCB( SERVER_ERROR_CODE failedcode){}

			/** ����ӿ�
				�����޸����뷵��
			*/
			virtual void onReqAccountNewPasswordCB( SERVER_ERROR_CODE failedcode){}

			/** 
				���playerʵ��
			*/
			KBEngineClient::Entity* pPlayer();

			void setPlayerPosition(float x, float y, float z){  entityPos_.x = x; entityPos_.y = y; entityPos_.z = z; /*entityPos_ = Vector3(x, y, z);*/ }
			void setPlayerDirection(float roll, float pitch, float yaw){ ;/*entityDir_ = Vector3(roll, pitch, yaw); */}

			void setTargetID(ENTITY_ID id){ 
				targetID_ = id; 
				onTargetChanged();
			}
			ENTITY_ID getTargetID()const{ return targetID_; }
			virtual void onTargetChanged(){}

			ENTITY_ID getAoiEntityID(ENTITY_ID id);
			ENTITY_ID getAoiEntityIDFromStream(MemoryStream& s);
			ENTITY_ID getAoiEntityIDByAliasID(uint8 id);

			/** 
				space��ز����ӿ�
				����������ĳ��space�ļ���ӳ��
			*/
			void addSpaceGeometryMapping(SPACE_ID spaceID, const std::string& respath);
			virtual void onAddSpaceGeometryMapping(SPACE_ID spaceID, const std::string& respath){}
			virtual void onLoadedSpaceGeometryMapping(SPACE_ID spaceID){
				isLoadedGeometry_ = true;
			}

			const std::string& getGeometryPath();
	
			void initSpaceData( MemoryStream& s);
			void setSpaceData( SPACE_ID spaceID, const std::string& key, const std::string& value);
			void delSpaceData( SPACE_ID spaceID, const std::string& key);
			bool hasSpaceData(const std::string& key);
			const std::string& getSpaceData(const std::string& key);
	protected:				
			int32													appID_;

			// ���������ͨ��
			//Mercury::Channel*										pServerChannel_;
			KNetworkInterface*										pServerChannel_;

			// �洢���е�entity������
			//Entities<client::Entity>*								pEntities_;	
			std::map<ENTITY_ID,KBEngineClient::Entity*>				*pEntities_;
			std::vector<ENTITY_ID>									pEntityIDAliasIDList_;

			//PY_CALLBACKMGR											pyCallbackMgr_;

			ENTITY_ID												entityID_;
			SPACE_ID												spaceID_;
			std::string												entity_type_;

			//Position3D												entityPos_;
			//Direction3D												entityDir_;
		 
			Vector3													entityPos_;
			Vector3													entityDir_;

			DBID													dbid_;

			std::string												ip_;
			uint16													port_;

			uint64													lastSentActiveTickTime_;
			uint64													lastSentUpdateDataTime_;

			bool													connectedGateway_;
			bool													canReset_;

			std::string												name_;
			std::string												password_;
			std::string												extradatas_;

			CLIENT_CTYPE											typeClient_;

			//typedef std::map<ENTITY_ID, KBEShared_ptr<MemoryStream> > BUFFEREDMESSAGE;
			//BUFFEREDMESSAGE											bufferedCreateEntityMessage_;
			std::map<ENTITY_ID, MemoryStream>					bufferedCreateEntityMessage_;
	
			//EventHandler											eventHandler_;

			//Mercury::NetworkInterface&								ninterface_;
			KNetworkInterface*										networkInterface_;

			// ��ǰ�ͻ�����ѡ���Ŀ��
			ENTITY_ID												targetID_;

			// �Ƿ���ع���������
			bool													isLoadedGeometry_;

			SPACE_DATA												spacedatas_;
			
			//
		};

		///////////////////////////////////////////////////////////////////////////////////////////

		class ClientApp : 
			public ClientObjectBase
		{
			public:	
				static ClientApp& getInstance()
				{
					static ClientApp instance;
					return instance;
				}
	
	
		};

}

#endif /* defined(__libKBEClient__KNetworkInterface__) */
