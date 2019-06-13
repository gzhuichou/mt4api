#ifndef __MT4_API_H
#define __MT4_API_H

#include <Windows.h>
//+------------------------------------------------------------------+
//| version   1.0.0.0                          				         |
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+
//| Data Servers configuration                                       |
//+------------------------------------------------------------------+
struct Mt4_stConDataServer
  {
   char              server[64];             // server address (server:ip)
   ULONG             ip;                     // server IP
   char              description[64];        // server description
   int               isproxy;                // can server be proxy?
   int               priority;               // priority: 0-7 base, 255-idle
   UINT              loading;                // server loading (UINT_MAX-server does not inform its loading)
   ULONG             ip_internal;            // internal IP address
   int               reserved[2];            // reserved
   Mt4_stConDataServer* __ptr32 next;         // internal (not used)
  };
  
//+------------------------------------------------------------------+
//| demo account info                                             	 |
//+------------------------------------------------------------------+
struct Mt4_stDemoAccount
{
	UINT nLogin;
	char szPassword[8];	//	main password
	char szInvPass[8]; 	//  inverst password
};


//+------------------------------------------------------------------+
//| Quote Info                                             			 |
//+------------------------------------------------------------------+
struct Mt4_stQuoteEventInfo
{
	char szSymbol[12];	//   symbol name
	int nCount;			//   symbol count
	int nDigits;		//   symbol digits
	int nTime;			//   quote time
	double fAsk;			//   ask
	double fBid;			//   bid
};

//+------------------------------------------------------------------+
//| RateInfo                                             			 |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct Mt4_stRateInfo // 28
{
	__time32_t        ctm;                    //   rate time
	int               open;                   //   open price: 
	int               high, low, close;       //   high,low,close shift from open
	double            vol;                    //   volume
};
#pragma pack(pop)

//+------------------------------------------------------------------+
//| Security group configuration for client group                    |
//+------------------------------------------------------------------+
#define MAX_SEC_GROUPS       (32)
#define MAX_SEC_GROPS_MARGIN (128)
//---
struct Mt4_stConGroupSec
  {
   int               show,trade;            // enable show and trade for this group of securites
   int               execution;             // dealing mode-EXECUTION_MANUAL,EXECUTION_AUTO,EXECUTION_ACTIVITY
   //--- comission settings
   double            comm_base;             // standart commission
   int               comm_type;             // commission type-COMM_TYPE_MONEY,COMM_TYPE_PIPS,COMM_TYPE_PERCENT
   int               comm_lots;             // commission lots mode-COMMISSION_PER_LOT,COMMISSION_PER_DEAL
   double            comm_agent;            // agent commission
   int               comm_agent_type;       // agent commission mode-COMM_TYPE_MONEY, COMM_TYPE_PIPS
   //---
   int               spread_diff;           // spread difference in compare with default security spread
   //---
   int               lot_min,lot_max;       // allowed minimal and maximal lot values
   int               lot_step;              // allowed step value (10 lot-1000, 1 lot-100, 0.1 lot-10)
   int               ie_deviation;          // maximum price deviation in Instant Execution mode
   int               confirmation;          // use confirmation in Request mode
   int               trade_rights;          // clients trade rights-bit mask see TRADE_DENY_NONE,TRADE_DENY_CLOSEBY,TRADE_DENY_MUCLOSEBY
   int               ie_quick_mode;         // do not resend request to the dealer when client uses deviation
   int               autocloseout_mode;     // auto close-out method { CLOSE_OUT_NONE, CLOSE_OUT_HIHI, CLOSE_OUT_LOLO, CLOSE_OUT_HILO, CLOSE_OUT_LOHI, CLOSE_OUT_LOHI, CLOSE_OUT_FIFO, CLOSE_OUT_LIFO, CLOSE_OUT_INTRDAY_FIFO }
   double            comm_tax;              // commission taxes
   int               comm_agent_lots;       // agent commission per lot/per deal { COMMISSION_PER_LOT,COMMISSION_PER_DEAL }
   int               freemargin_mode;       // "soft" margin check
   int               reserved[3];           // reserved
  };
//+------------------------------------------------------------------+
//| Special securities configurations for client group               |
//+------------------------------------------------------------------+
struct Mt4_stConGroupMargin
  {
   char              symbol[12];            // security
   double            swap_long,swap_short;  // swap size for long and short positions
   double            margin_divider;        // margin divider
   int               reserved[7];
  };
//--- dealing mode
enum { EXECUTION_MANUAL, EXECUTION_AUTO, EXECUTION_ACTIVITY };
//--- commission type
enum { COMM_TYPE_MONEY, COMM_TYPE_PIPS, COMM_TYPE_PERCENT };
//--- comission lots mode
enum { COMMISSION_PER_LOT, COMMISSION_PER_DEAL };
//--- clients trade rights
enum { TRADE_DENY_NONE=0, TRADE_DENY_CLOSEBY=1, TRADE_DENY_MUCLOSEBY=2 };
//--- auto close-out method
enum { CLOSE_OUT_NONE, CLOSE_OUT_HIHI, CLOSE_OUT_LOLO, CLOSE_OUT_HILO, CLOSE_OUT_LOHI, CLOSE_OUT_FIFO, CLOSE_OUT_LIFO, CLOSE_OUT_INTRDAY_FIFO };
//+------------------------------------------------------------------+
//| Client group configuration                                       |
//+------------------------------------------------------------------+
struct Mt4_stConGroup
  {
   //--- common settings
   char              group[16];                   // group name
   int               enable;                      // enable group
   int               timeout;                     // trade confirmation timeout (seconds)
   int               otp_mode;                    // one-time password mode
   //--- statements
   char              company[128];                // company name
   char              signature[128];              // statements signature
   char              support_page[128];           // company support page
   char              smtp_server[64];             // statements SMTP server
   char              smtp_login[32];              // statements SMTP login
   char              smtp_password[32];           // statements SMTP password
   char              support_email[64];           // support email
   char              templates[32];               // path to directory with custom templates
   int               copies;                      // copy statements on support email
   int               reports;                     // enable statements
   //--- default settings
   int               default_leverage;            // default leverage (user don't specify leverage himself)
   double            default_deposit;             // default deposit  (user don't specify balance  himself)
   //--- securities
   int               maxsecurities;               // maximum simultaneous securities
   Mt4_stConGroupSec       secgroups[MAX_SEC_GROUPS];   // security group settings
   Mt4_stConGroupMargin    secmargins[MAX_SEC_GROPS_MARGIN]; // special securities settings
   int               secmargins_total;            // count of special securities settings
   //--- margin & interest
   char              currency[12];                // deposit currency
   double            credit;                      // virtual credit
   int               margin_call;                 // margin call level (percents)
   int               margin_mode;                 // margin mode-MARGIN_DONT_USE,MARGIN_USE_ALL,MARGIN_USE_PROFIT,MARGIN_USE_LOSS
   int               margin_stopout;              // stop out level
   double            interestrate;                // annual interest rate (percents)
   int               use_swap;                    // use rollovers & interestrate
   //--- rights
   int               news;                        // news mode
   int               rights;                      // rights bit mask-ALLOW_FLAG_EMAIL
   int               check_ie_prices;             // check IE prices on requests
   int               maxpositions;                // maximum orders and open positions
   int               close_reopen;                // partial close mode (if !=0 original position will be fully closed and remain position will be fully reopened)
   int               hedge_prohibited;            // hedge prohibition flag
   int               close_fifo;                  // fifo rule 
   int               hedge_largeleg;              // use large leg margin for hedged positions
   int               unused_rights[2];            // reserved

   char              securities_hash[16];         // internal data
   //---
   int               margin_type;                 // margin controlling type { MARGIN_TYPE_PERCENT,  MARGIN_TYPE_CURRENCY }
   //--- archives
   int               archive_period;              // inactivity period after which account moves to archive base (in days)
   int               archive_max_balance;         // maxumum balance of accounts to move in archive base
   //---
   int               stopout_skip_hedged;         // skip fully hedged accounts when checking for stopout
   int               archive_pending_period;      // pendings clean period
   //--- allowed news languages
   UINT              news_languages[8];           // LANGID array
   UINT              news_languages_total;        // news languages total
   //--- reserved
   int               reserved[17];
  };
//--- margin calculation mode
enum { MARGIN_MODE_DONT_USE,MARGIN_MODE_USE_ALL,MARGIN_MODE_USE_PROFIT,MARGIN_MODE_USE_LOSS };
//--- margin controlling type
enum { MARGIN_TYPE_PERCENT, MARGIN_TYPE_CURRENCY };
//--- news mode-no news, only topics, full news (topic+body)
enum { NEWS_NO, NEWS_TOPICS, NEWS_FULL  };
//--- group rights
enum 
  { 
   ALLOW_FLAG_EMAIL           =1,
   ALLOW_FLAG_TRAILING        =2,
   ALLOW_FLAG_ADVISOR         =4,
   ALLOW_FLAG_EXPIRATION      =8,
   ALLOW_FLAG_SIGNALS_ALL     =16,
   ALLOW_FLAG_SIGNALS_OWN     =32,
   ALLOW_FLAG_RISK_WARNING    =64,
   ALLOW_FLAG_FORCED_OTP_USAGE=128,
  };
//--- group one-time password mode
enum
  {
   OTP_MODE_DISABLED       =0,
   OTP_MODE_TOTP_SHA256    =1,
  };
  

//| Symbol configurations                                            |
//+------------------------------------------------------------------+
//| Symbol sessions configurations                                   |
//+------------------------------------------------------------------+
struct Mt4_stConSession //32 ，4字节对齐
{
	short             open_hour, open_min;          //   session open  time: hour & minute
	short             close_hour, close_min;        //   session close time: hour & minute
	int               open, close;                  //   internal data
	short             align[7];                     //  internal data
};
//---
struct Mt4_stConSessions //208 ，4字节对齐
{
	//---
	Mt4_stConSession        quote[3];               //  quote sessions
	Mt4_stConSession        trade[3];               //  trade sessions
													//---
	int               quote_overnight;             	// internal data
	int               trade_overnight;             	// internal data
	int               reserved[2];                 	// reserved
};

//+------------------------------------------------------------------+
//| Symbol configuration                                             |
//+------------------------------------------------------------------+
#define MAX_SYMBOLS 1024
//---
struct Mt4_stConSymbol // 1936
{
	//--- common settings
   char              symbol[12];                  // name
   char              description[64];             // description
   char              source[12];                  // synonym
   char              currency[12];                // currency
   int               type;                        // security group (see ConSymbolGroup)
   int               digits;                      // security precision
   int               trade;                       // trade mode
   //--- external settings
   COLORREF          background_color;            // background color
   int               count;                       // symbols index
   int               count_original;              // symbols index in market watch
   int               external_unused[7];
   //--- sessions
   int               realtime;                    // allow real time quotes
   __time32_t        starting;                    // trades starting date (UNIX time)
   __time32_t        expiration;                  // trades end date      (UNIX time)
   Mt4_stConSessions       sessions[7];                 // quote & trade sessions
   //--- profits
   int               profit_mode;                 // profit calculation mode
   int               profit_reserved;             // reserved
   //--- filtration
   int               filter;                      // filter value
   int               filter_counter;              // filtration parameter
   double            filter_limit;                // max. permissible deviation from last quote (percents)
   int               filter_smoothing;            // smoothing
   float             filter_reserved;             // reserved
   int               logging;                     // enable to log quotes
   //--- spread & swaps
   int               spread;                      // spread
   int               spread_balance;              // spread balance
   int               exemode;                     // execution mode
   int               swap_enable;                 // enable swaps
   int               swap_type;                   // swap type
   double            swap_long,swap_short;        // swaps values for long & short postions
   int               swap_rollover3days;          // triple rollover day-0-Monday,1-Tuesday...4-Friday
   double            contract_size;               // contract size
   double            tick_value;                  // one tick value
   double            tick_size;                   // one tick size
   int               stops_level;                 // stops deviation value
   //---
   int               gtc_pendings;                // GTC mode { ORDERS_DAILY, ORDERS_GTC, ORDERS_DAILY_NO_STOPS }
   //--- margin calculation
   int               margin_mode;                 // margin calculation mode
   double            margin_initial;              // initial margin
   double            margin_maintenance;          // margin maintenance
   double            margin_hedged;               // hedged margin
   double            margin_divider;              // margin divider
   //--- calclulated variables (internal data)
   double            point;                       // point size-(1/(10^digits)
   double            multiply;                    // multiply 10^digits
   double            bid_tickvalue;               // tickvalue for bid
   double            ask_tickvalue;               // tickvalue for ask
   //---
   int               long_only;                   // allow only BUY positions
   int               instant_max_volume;          // max. volume for Instant Execution
   //---
   char              margin_currency[12];         // currency of margin requirments
   int               freeze_level;                // modification freeze level
   int               margin_hedged_strong;        // strong hedged margin mode
   __time32_t        value_date;                  // value date
   int               quotes_delay;                // quotes delay after session start
   int               swap_openprice;         	  // use open price at swaps calculation in SWAP_BY_INTEREST mode
   int               swap_variation_margin;       // charge variation margin on rollover
   //---
   int               unused[21];             	  // reserved

};

//+------------------------------------------------------------------+
//| Symbols enumeration                                              |
//+------------------------------------------------------------------+
//--- symbol execution mode
enum { EXE_REQUEST,EXE_INSTANT,EXE_MARKET };
//--- trade mode
enum { TRADE_NO,TRADE_CLOSE,TRADE_FULL };
//--- swap type
enum { SWAP_BY_POINTS,SWAP_BY_DOLLARS,SWAP_BY_INTEREST,SWAP_BY_MARGIN_CURRENCY };
//--- profit calculation mode
enum { PROFIT_CALC_FOREX,PROFIT_CALC_CFD,PROFIT_CALC_FUTURES };
//--- margin calculation mode
enum { MARGIN_CALC_FOREX,MARGIN_CALC_CFD,MARGIN_CALC_FUTURES,MARGIN_CALC_CFDINDEX,MARGIN_CALC_CFDLEVERAGE };
//--- GTC mode
enum { ORDERS_DAILY, ORDERS_GTC, ORDERS_DAILY_NO_STOPS };

//+------------------------------------------------------------------+
//| Symbol groups                                                    |
//+------------------------------------------------------------------+
#define MAX_SEC_GROUP (32)
struct Mt4_stConSymbolGroup //80
{
	char              name[16];                    // group name
	char              description[64];             // group description
};

//+------------------------------------------------------------------+
//| Trade Record                                                     |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct Mt4_stTradeRecord
  {
   int               order;            // order ticket
   int               login;            // owner's login
   char              symbol[12];       // security
   int               digits;           // security precision
   int               cmd;              // trade command
   int               volume;           // volume
   //---
   __time32_t        open_time;        // open time
   int               state;            // reserved
   double            open_price;       // open price
   double            sl,tp;            // stop loss & take profit
   __time32_t        close_time;       // close time
   int               gw_volume;        // gateway order volume
   __time32_t        expiration;       // pending order's expiration time
   char              reason;           // trade reason
   char              conv_reserv[3];   // reserved fields
   double            conv_rates[2];    // convertation rates from profit currency to group deposit currency
                                       // (first element-for open time, second element-for close time)
   double            commission;       // commission
   double            commission_agent; // agent commission
   double            storage;          // order swaps
   double            close_price;      // close price
   double            profit;           // profit
   double            taxes;            // taxes
   int               magic;            // special value used by client experts
   char              comment[32];      // comment
   int               gw_order;         // gateway order ticket
   int               activation;       // used by MT Manager
   short             gw_open_price;    // gateway order price deviation (pips) from order open price
   short             gw_close_price;   // gateway order price deviation (pips) from order close price
   double            margin_rate;      // margin convertation rate (rate of convertation from margin currency to deposit one)
   __time32_t        timestamp;        // timestamp
   int               api_data[4];      // for api usage
   Mt4_stTradeRecord *__ptr32 next;          // internal data
  };
#pragma pack(pop)
//--- trade commands
enum { OP_BUY=0,OP_SELL,OP_BUY_LIMIT,OP_SELL_LIMIT,OP_BUY_STOP,OP_SELL_STOP,OP_BALANCE,OP_CREDIT };

//---------------------------
enum  Mt4_emOrderProgressType
{
    TPT_Rejected,		//拒绝
    TPT_Accepted,		//接受
    TPT_InProcess,		//处理中
    TPT_Opened,			//开仓
    TPT_Closed,			//平仓
    TPT_Modified,		//修改
    TPT_PendingDeleted,	//删除挂单
    TPT_ClosedBy,		//对冲平仓
    TPT_MultipleClosedBy,//同一证券多订单对冲平仓
    TPT_Timeout,		//超时
    TPT_Price,			//获取价格
    TPT_Cancel,			//取消
	TPT_UNKNOW,
};

struct Mt4_stOrderNotifyEventInfo
{
    int nReqId;
    unsigned char nStatus;
    Mt4_emOrderProgressType emType;
    Mt4_stTradeRecord  tr;
    double bid;
    double ask;
};

//--------------
enum Mt4_emOrderUpdateAction
{
    OUA_PositionOpen,	//开仓
    OUA_PositionClose,	//平仓
    OUA_PositionModify,	//修改
    OUA_PendingOpen,	//挂单
    OUA_PendingDelete,	//删除挂单
    OUA_PendingModify,	//挂单修改
    OUA_PendingFill,	//挂单触发
    OUA_Balance,		//余额
    OUA_Credit,			//信用
};


struct Mt4_stOrderUpdateEventInfo
{
	Mt4_emOrderUpdateAction emUpdateAction;
	double fBalance;
	double fCredit;
	Mt4_stTradeRecord tr;
};

//-----------------------------
#ifdef __cplusplus
extern "C" {
#endif

int  WINAPI MT4API_Create();
void WINAPI MT4API_Destory(const int nID);

int	 WINAPI MT4API_GetLastError(const int nID, const int nPos);
bool WINAPI MT4API_GetErrorDescription(const int nErrCode, const char *pszErrDesc, const int nSize);
bool WINAPI MT4API_GetLastErrorDescription(const int nID, const char *pszErrDesc, const int nSize, const int nPos);
//-----------------

bool WINAPI MT4API_CreateDemoAccount(
	const char* pszHost,
	const int nPort,
	const int nLeverage,
	const double fBalance,
	const char *pszName,
	const char *pszAccountType,
	const char *pszCountry,
	const char *pszCity,
	const char *pszState,
	const char *pszZip,
	const char *pszAddress,
	const char *pszPhone,
	const char *pszEmail,
	const char *pszTerminalCompany,
	Mt4_stDemoAccount &Account);
//------------------------
bool WINAPI MT4API_Init(
	const int nID,
	const char* pszBroker,
	const unsigned int nUser,
	const char *pszPassword,
	const char *pszHost,
	const int nPort,
	const int nTradeHisTimeFrom,
	const int nTradeHisTimeTo);
bool WINAPI MT4API_Connect(const int nID);
bool WINAPI MT4API_SetDisconnectEventHandler(const int nID, LPVOID pHandler, LPVOID param = nullptr);
bool WINAPI MT4API_DisConnect(const int nID);
bool WINAPI MT4API_IsConnect(const int nID);

bool WINAPI MT4API_GetUser(const int nID, unsigned int &nUser);
bool WINAPI MT4API_GetUserName(const int nID, const char * pUserName, const int nSize);
bool WINAPI MT4API_GetUserGroup(const int nID, Mt4_stConGroup &group);
bool WINAPI MT4API_IsDemoAccount(const int nID);
bool WINAPI MT4API_GetServerTime(const int nID, int &nTime);
bool WINAPI MT4API_GetServerBuild(const int nID, unsigned short &nServerBuild);
bool WINAPI MT4API_GetSeverInfoCount(const int nID, int &nServerInfoCount);
bool WINAPI MT4API_GetSeverInfos(const int nID, const  Mt4_stConDataServer *pServerInfos, int &nCount);

bool WINAPI MT4API_GetMoneyInfo(const int nID, double &fBalance, double &fCredit, double &fMargin, double &fFreeMargin, double &fEquity, double &fProfit);
bool WINAPI MT4API_GetFreeMargin(const int nID, double &fFreeMargin);
bool WINAPI MT4API_GetMargin(const int nID, double &fMargin);
bool WINAPI MT4API_GetBalance(const int nID, double &fBalance);
bool WINAPI MT4API_GetCredit(const int nID, double &fCredit);
bool WINAPI MT4API_GetProfit(const int nID, double &fProfit);
bool WINAPI MT4API_GetEquity(const int nID, double &fEquity);
bool WINAPI MT4API_GetLeverage(const int nID, int &nLeverage);


bool WINAPI MT4API_GetSymbolInfo(const int nID, const char *pszSymbolName, Mt4_stConSymbol &symbol);
bool WINAPI MT4API_GetSymbolsCount(const int nID, int &nSymbolCount);
bool WINAPI MT4API_GetSymbolsInfo(const int nID, const Mt4_stConSymbol * pSymbols, int &nCount);
bool WINAPI MT4API_GetSymbolGroups(const int nID, const Mt4_stConSymbolGroup *pGroups, int &nCount);

bool WINAPI MT4API_IsSubscribe(const int nID, const char *pszSymbolName);
bool WINAPI MT4API_Subscribe(const int nID, const char *pszSymbolName);
bool WINAPI MT4API_UnSubscribe(const int nID, const char *pszSymbolName);

bool WINAPI MT4API_DownloadQuoteHistory(const int nID, const char *pszSymbolName, const int nPeroid, const int nTimeFrom, const short nCount);
bool WINAPI MT4API_SetQuoteHistoryEventHandler(const int nID, LPVOID pHandler, LPVOID param = nullptr);

bool WINAPI MT4API_GetQuote(const int nID, const char *pszSymbolName, Mt4_stQuoteEventInfo &Info);
bool WINAPI MT4API_SetQuoteEventHandler(const int nID, LPVOID pHandler, LPVOID param = nullptr);


bool WINAPI MT4API_GetCloseOrder(const int nID, const int nOrder, Mt4_stTradeRecord &tr);
bool WINAPI MT4API_GetCloseOrdersCount(const int nID, int &nOrderCount);
bool WINAPI MT4API_GetCloseOrders(const int nID, const Mt4_stTradeRecord *pOrders, int &nCount);
bool WINAPI MT4API_GetOpenOrder(const int nID, const int nOrder, Mt4_stTradeRecord &tr);
bool WINAPI MT4API_GetOpenOrdersCount(const int nID, int &nOrderCount);
bool WINAPI MT4API_GetOpenOrders(const int nID, const Mt4_stTradeRecord *pOrders, int &nCount);
//-------------------
bool WINAPI MT4API_IsTradeAllowed(const int nID);
bool WINAPI MT4API_SetOrderNotifyEventHandler(const int nID, LPVOID pHandler, LPVOID param = nullptr);
bool WINAPI MT4API_SetOrderUpdateEventHandler(const int nID, LPVOID pHandler, LPVOID param = nullptr);
bool WINAPI MT4API_GetTradeHistoryCount(const int nID, const int nTimeFrom, const int nTimeTo, int &nOrderCount);
bool WINAPI MT4API_DownloadTradeHistory(const int nID, const Mt4_stTradeRecord *pOrders, int &nCount);

//
bool WINAPI MT4API_OrderSend(
	const int nID,
	const char  *pszSymbol,
	unsigned char nTradeCmd,
	const double volume,
	const double price,
	const int ie_deviation,
	const double stoploss,
	const double takeprofit,
	const char  *pszComment,
	const int magic,
	const int expiration,
	Mt4_stTradeRecord &TradeRecord);

int WINAPI MT4API_OrderSendAsync(
	const int nID,
	const char  *pszSymbol,
	unsigned char nTradeCmd,
	const double volume,
	const double price,
	const int ie_deviation,
	const double stoploss,
	const double takeprofit,
	const char  *pszComment,
	const int magic,
	const int expiration);

bool WINAPI MT4API_OrderClose(
	const int nID,
	const char  *pszSymbol,
	const int order,
	const double volume,
	const double price,
	const int ie_deviation,
	Mt4_stTradeRecord &TradeRecord);

int WINAPI MT4API_OrderCloseAsync(
	const int nID,
	const char  *pszSymbol,
	const int order,
	const double volume,
	const double price,
	const int ie_deviation);

bool WINAPI MT4API_OrderCloseBy(const int nID, const int order1, const int order2);
int  WINAPI MT4API_OrderCloseByAsync(const int nID, const  int order1, const int order2);

bool WINAPI MT4API_OrderMultipleCloseBy(const int nID, const char  *pszSymbol);
int  WINAPI MT4API_OrderMultipleCloseByAsync(const int nID, const char  *pszSymbol);

bool WINAPI MT4API_OrderDelete(const int nID, const int order);
int  WINAPI MT4API_OrderDeleteAsync(const int nID, const int order);

bool WINAPI MT4API_OrderModify(
	const int nID,
	unsigned char nTradeCmd,
	const int order,
	const double price,
	const double stoploss,
	double takeprofit,
	const int expiration,
	Mt4_stTradeRecord &TradeRecord);

int WINAPI MT4API_OrderModifyAsync(
	const int nID,
	unsigned char nTradeCmd,
	const int order,
	const double price,
	const double stoploss,
	double takeprofit,
	const int expiration);

#ifdef __cplusplus
}
#endif

#endif
