#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "cgicommon.h"
#include "html-lib.h"
#include "cgi-lib.h"
#include "string-lib.h"
#include "ini.h"
#include "ucfg_lib.h"
//#define LANUAGE    1



static pthread_cond_t cgi_cond  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t cgi_lock  = PTHREAD_MUTEX_INITIALIZER;
char langbuf[] = 
#if 1
{"{\
type:[\"English\", \"简体中文\"],\
info:[\{\
			h_ban:\
			{\
				title:\"PON Banner\",\
				innerHTML:\
				{\
					in_st:\"Status\,\
					in_se:\"Setup\",\
					in_ma:\"Management\",\
					in_us:\"User\",\
				}\
			},\
			h_tr069:\
			{\
				title:\"\",\
				innerHTML:\
				{\
					in_tr069_cfgid:\"TR-069 Configure\",\
					in_tr069_Enable:\"Enable\",\
					id_disable_tb:\"<input type=\"radio\" name=\"autoexec\" value=\"0\" id=\"Disable\">Disable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"autoexec\" value=\"1\" id=\"Enable\">Enable&nbsp;&nbsp;&nbsp;\",\
					in_Enable:\"Enable\",\
					in_url:\"url\",\
					in_uname:\"username\",\
					in_pwd:\"password\",\
					in_periodic_inform_enable:\"periodic inform enable\",\
					id_disable_info_tb:\"<input type=\"radio\" name=\"enable\" value=\"0\" checked onClick=\"return periodicSel()\">Disable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"enable\" value=\"1\" onClick=\"return periodicSel()\">Enable&nbsp;&nbsp;&nbsp;\",\
					in_periodic_inform_interval:\"periodic inform interval\",\
					in_id_interface_tb:\"<img src=\"./img/tick.png\" >&nbsp;Connection Request\",\
					in_port:\"port\",\
				},\
				value:\
				{\
					bt_apply:\"Start UNI loopback test\",\
					in_apply:\"Apply\",\
				},\
				js_string:\
				{\
					str_alert_url_empty:\"Url is empty\",\
					str_alert_restart_set:\"Setting has been changed.\nNeed to reboot for the value to take effect\",\
					str_alert_uname_empty:\"user name is empty\",\
					str_alert_pwd_empty:\"password is empty\",\
					str_alert_interval_empty:\"interval is empty!\",\
					str_alert_interval_invalid:\"interval is invalid!\",\
					str_alert_setting_change:\"Setting has been changed.\nNeed to reboot for the value to take effect\",\
					str_alert_port_empty:\"port is empty!\",\
					str_alert_server_url_empty:\"STUN server url is empty\",\
					str_alert_server_url_invalid:\"STUN server url length is invalid(Valid range length: 0 ~ 128)\",\
					str_alert_server_port_empty:\"STUN server port is empty\",\
					str_alert_nan:\" is not a number\",\
					str_alert_invalid:\"is invalid (Valid range: 1 ~ 65535)\"\
				}\
			},\
			h_gct:\
			{\
				title:\"System Information\",\
				innerHTML:\
				{\
					in_id_sys_info_tb:\"<img src=\"./img/tick.png\">&nbsp; System Information\",\
					in_id_device_name:\"Device Name\",\
					in_id_FW_tb:\"FirmwareVersion\",\
					in_id_device_HW_tb:\"DeviceVersion\",\
					in_id_FW_date_tb:\"FirmwareDate\"\
				},\
			},\
			h_net:\
			{\
				title:\"Network Information\",\
				innerHTML:\
				{\
					in_id_interface_tb:\"<img src=\"./img/tick.png\">&nbsp;Interfaces\",\
					in_id_name:\"name\",\
					in_id_netmask:\"NETMASK\",\
					in_id_status:\"Status\",\
					in_id_Gateway_Route_DNS_tb:\"<img src=\"./img/tick.png\">&nbsp;Gateway,Route, DNS \",\
					in_id_default_Gateway_tb:\"Default Gateway\",\
					in_id_primary_dns_tb:\"Primary DNS\",\
					in_id_remote_ip_tb:\"Remote IP (Your IP)\",\
					in_id_secondary_dns_tb:\"Secondary DNS\",\
					in_id_close_tb:\"Off\",\
					in_id_open_tb:\"On\",\
					in_id_dhcp_server:\"DHCP Server\",\
					in_id_ip_addr_tb:\"IP address\",\
					in_id_subnet_mask:\"Subnet Mask\",\
					in_id_gateway_tb:\"Gateway\",\
					in_id_dhcp_addr_allocation_tb:\"DHCP Address Allocation\",\
					in_id_close_nat_tb:\"Off\",\
					in_id_open_nat_tb:\"On\",\
					in_id_enable_tb:\"Enable\",\
					in_id_close_ipv6_tb:\"Off\",\
					in_id_open_ipv6_tb:\"On\",\
					in_id_prefix_len_tb:\"Prefix len\"\
				},\
				value:\
				{\
					ButtonSetBridge:\"Apply\",\
					BTN_IPV6:\"Apply\",\
				},\
				js_string:\
				{\
					str_alert_url_empty_value:\"Empty value\",\
					str_alert_nan:\"is not a number\",\
					str_alert_not_valid_ip:\"is not a valid IP\",\
					str_alert_check_value:\"Check values\",\
					str_alert_prefix_empty:\"Prefix len is empty\",\
					str_alert_invalid:\"is invalid (Valid range: 0 ~ 128)\",\
					str_alert_setting_change:\"Setting has been changed.\nNeed to reboot for the value to take effect\",\
				}\
			},\
			h_portforwarding:\
			{\
				title:\"NAT/Router Manager\",\
				innerHTML:\
				{\
					in_id_portforward_setting_tb:\"<img src=\"./img/tick.png\"/>&nbsp; Port Forwarding Setting\",\
					in_id_Rule_name_tb:\"Rule name\",\
					in_id_maximum_length_tb:\"<input type=\"text\" id=\"rule_name\" class=\"inputtext\" onkeypress=\"on_key_press_rulename(this)\" onblur=\"on_key_press_rulename(this)\" style=\"width: 100px\" maxlength=\"20\"/>&nbsp; (The maximum length is 20 characters.)\",\
					id_ip_addr_tb:\"IP address\",\
					in_id_lable_tb:\"Set to the HOST PC IP address (<span id=\"RemoteIPAddress1\"></span>)\",\
					in_id_Protocol_tb:\"Protocol\",\
					id_extern_port_tb:\"External port\",\
					id_inter_port_tb:\"Internal port\",\
					in_id_add_tb:\"	<input type=\"button\" class=\"pbutton\" value=\"Add\" onclick=\"port_forwarding_table_add()\">\",\
					in_id_portforward_tb:\"<img src=\"./img/tick.png\"/>&nbsp; Port Forwarding Tables\",\
					in_id_No_tb:\"No.\",\
					in_id_rule_name_tb:\"Rule name\",\
					in_id_Ip_addr_tb:\"Ip address\",\
					in_id_protocol_tb:\"Protocol\",\
					in_id_extern_port_tbl:\"External port\",\
					in_id_inter_port_tbl:\"Internal port\",\
					in_id_delete_tb:\"Delete\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Apply\" id=\"btnport\" onclick=\"SetPortRuleSetting()\">\",\
					in_id_ftp_tb:\"<input type=\"radio\" name=\"nf_ftp\" id=\"nf_ftp\" value=\"1\" >Enable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_ftp\" id=\"nf_ftp\" value=\"0\">Disable&nbsp;&nbsp;&nbsp;\",\
					in_id_nfh323_tb:\"<input type=\"radio\" name=\"nf_h323\" id=\"nf_h323\" value=\"1\" >Enable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_h323\" id=\"nf_h323\" value=\"0\">Disable&nbsp;&nbsp;&nbsp;\",\
					in_id_nf_sip_tb:\"<input type=\"radio\" name=\"nf_sip\" id=\"nf_sip\" value=\"1\" >Enable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_sip\" id=\"nf_sip\" value=\"0\">Disable&nbsp;&nbsp;&nbsp;\",\
					in_id_nf_pptp_tb:\"<input type=\"radio\" name=\"nf_pptp\" id=\"nf_pptp\" value=\"1\" >Enable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_pptp\" id=\"nf_pptp\" value=\"0\">Disable&nbsp;&nbsp;&nbsp;\",\
					in_id_nf_tftp_tb:\"<input type=\"radio\" name=\"nf_tftp\" id=\"nf_tftp\" value=\"1\" >Enable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_tftp\" id=\"nf_tftp\" value=\"0\">Disable&nbsp;&nbsp;&nbsp;\",\
					in_id_epply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"SetALGMode()\">\",\
					in_id_upnp_enable_tb:\"<input type=\"radio\" name=\"upnp_enable\" id=\"upnp_enable\" value=\"1\" >Enable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"upnp_enable\" id=\"upnp_enable\" value=\"0\">Disable&nbsp;&nbsp;&nbsp;\",\
					in_id_appli_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"SetUPNPMode()\">\",\
					in_id_DMZ_tb:\"<img src=\"./img/tick.png\"/>&nbsp; DMZ Setting\",\
					in_id_inter_addr_tb:\"Internal IP address\",\
					in_id_host_addr_tb:\"Set to the HOST PC IP address(<span id=\"RemoteIPAddress2\"></span>)\",\
					in_btnDMZsetting:\"Apply\",\
					in_btnDMZsetting_tb:\"Stop\",\
					in_id_MAC_tb:\"<input type=\"checkbox\" value=\"0\" id=\"mac_checkbox0\" onclick=\"mac_filtering_step(this)\" checked=\"checked\"/><label for=\"mac_checkbox0\"><span>All allow</span></label>&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" value=\"1\" id=\"mac_checkbox1\" onclick=\"mac_filtering_step(this)\" /><label for=\"mac_checkbox1\"><span>Only allow registered address</span></label>&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" value=\"2\" id=\"mac_checkbox2\" onclick=\"mac_filtering_step(this)\" /><label for=\"mac_checkbox2\"><span>Only reject registered address</span></label>&nbsp;&nbsp;<input type=\"button\" class=\"pbutton\" value=\"Connected mac Search\" style=\"width:160px\" onclick=\"mac_pop()\"/>\",\
					in_id_mac_filter_tb:\"<img src=\"./img/tick.png\"/>&nbsp; MAC Filter\",\
					in_id_mac_addr_tb:\"MAC address \",\
					in_id_Add_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Delete\" onclick=\"MAC_list_table_add()\"/>\",\
					in_id_MAC_tbl:\"<img src=\"./img/tick.png\"/>&nbsp; MAC List\",\
					in_id_no_tb:\"No.&nbsp;\",\
					in_id_mac_tb:\"MAC address\",\
					in_id_del_tb:\"Delete\",\
					in_id_eppliy_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Apply\" onclick=\"SetMACfilter()\">\",\
					in_cell_innerHTML:\"' value='Delete'; onclick='port_forwarding_table_delete()'>\",\
					in_cell_innerHTML_tb:\"' value='Delete'; onclick='MAC_list_table_delete()'>\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_portforwarding:\"Can't support portforwarding no more items.\",\
					str_alert_no_rule_name:\"Did not insert rule name.\",\
					str_alert_special_char:\"Don't use special Character.\",\
					str_alert_ip_get:\"Not available IP address.\",\
					str_alert_External_port: \"Did not insert External port number.\",\
					str_alert_Not_available_inter_port: \"Not available External port number.\",\
					str_alert_Same_rule_name:\"Same rule name exist.\",\
					str_alert_MAC_filtering:\"Can't support MAC filtering no more items.\",\
					str_alert_not_available_address:\"Did not available MAC address.\",\
					str_alert_same_mac_exit:\"Same Mac address exist.\",\
					str_alert_not_get_mac_addr:\"Did not available MAC address.\",\
					str_alert_iptables_setting_complete:\"Iptables Setting Complete\",\
					str_alert_setting_change:\"Setting has been changed.\nNeed to reboot for the value to take effect\",\
					str_alert_not_available_ipadress:\"Not available IP address.\",\
					str_alert_not_use_this_ip:\"Can not use this IP address.\",\
					str_alert_DMZ_setting:\"DMZ Setting Complete.\",\
					str_alert_add_mac:\"you should add mac address.\",\
					str_alert_MAC_filter:\"MAC filtering complete.\",\
				},	\
			},\
			h_ntp:\
			{\
				title:\"NTP Configure\",\
				innerHTML:\
				{\
					in_id_sync_tb:\"<input size=\"24\" name=\"tmptime\" id = \"tmp_time\" value=\"\" type=\"text\" style=\"display:none\"><input size=\"24\" name=\"ntpcurrenttime\" id = \"current_time\" value=\"\" type=\"text\" readonly>&nbsp; &nbsp;<input type=\"button\" value=\"Sync with host\" id=\"manNTPSyncWithHost\" name=\"manNTPSyncWithHost\" onClick=\"syncWithHost()\">\",\
					in_manNTPCurrentTime:\"Current time:\",\
					in_manNTPTimeZone:\"TimeZone:\",\
					in_manNTPServer:\"NTP Server\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"manNTPApply\" value=\"Apply\" onclick=\"NTPFormCheck()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_setting_change:\"Setting has been changed.\nNeed to reboot for the value to take effect\",\
				},\
			},\
			h_sntp:\
			{\
				title:\"Config SNTP\",\
				innerHTML:\
				{\
					in_hd:\"SNTP Configuration \",\
					txt_step:\"Loading.....\",\
					in_intro:\"To enable SNTP, check the Enable SNTP box and enter a time server.\",\
					in_sntpsta_cur:\"SNTP is currently\",\
					in_dis:\"Disable SNTP\",\
					in_en:\"Enable SNTP\",\
					in_primsrvr:\"Primary SNTP Server:\",\
					in_secsrvr:\"Secondary SNTP Server:\",\
					in_tersrvr:\"Tertiary SNTP Server:\",\
					in_timeout:\"Timeout:\",\
					in_pollint:\"Polling Interval:\",\
					in_retrcnt:\"Retry Count:\",\
					in_tz:\"Time Zone:\",\
					in_dlight_cur:\"Day Light:\"\
				},\
				value:\
				{\
					bt_apply:\"Apply\"\
                },\
				option_text:\
				{\
					timezone:[\"(GMT-12:00) International Date Line West\",\
						\"(GMT-11:00) Midway Island\",\
						\"(GMT-10:00) Hawaii\",\
						\"(GMT-09:00) Alaska\",\
						\"(GMT-08:00) Pacific Time (US, Canada), Tijuana\",\
						\"(GMT-07:00) Arizona; Mountain Time (US, Canada)\",\
						\"(GMT-06:00) Central America; Central Time (US, Canada)\",\
						\"(GMT-05:00) Eastern Time (US, Canada)\",\
						\"(GMT-04:00) Atlantic Time (Canada)\",\
						\"(GMT-03:00) Brasilia; Buenos Aires; Greenland\",\
						\"(GMT-02:00) Mid-Atlantic\",\
						\"(GMT-01:00) Cape Vade\",\
						\"(GMT) Greenwhich Mean Time: Dublin, Lisbon, London; Casablanca\",\
						\"(GMT+01:00) Amsterdam, Berlin, Rome, Stockholm, Vienna, Paris\",\
						\"(GMT+02:00) Athens, Istanbul, Cairo, Harare, Jerusalem\",\
						\"(GMT+03:00) Baghdad, Kuwait, Riyadh, Moscow\",\
						\"(GMT+04:00) Muscat\",\
						\"(GMT+05:00) Islamabad, Karachi\",\
						\"(GMT+05:30) Chennai, Kolkata, Mumbai, New Delhi\",\
						\"(GMT+06:00) Dhaka\",\
						\"(GMT+07:00) Bangkok, Hanoi, Jakartha\",\
						\"(GMT+08:00) Beijing, Hong Kong\",\
						\"(GMT+09:00) Tokyo, Seoul\",\
						\"(GMT+10:00) Brisbane, Sydney\",\
						\"(GMT+11:00) Magadan, Solomon Islands\",\
						\"(GMT+12:00) Auckland, Wellington, Fiji\"]\
				},\
				js_string:\
				{\
					str_set_sntp:\SNTP Configuration \",\
					str_ok:\"successful.\",\
					str_failed:\"failed.\"\
				}\
            },\
            h_user:\
			{\
				title:\"USER\",\
				innerHTML:\
				{\
					in_id_pwd_setting_tb:\"<img src=\"./img/tick.png\">&nbsp;Password Configuration:\",\
					in_id_user_tb:\"USER\",\
					in_id_new_pwd_tb:\"New Password:\",\
					in_id_conform_pwd_tb:\"Confirmed Password:\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"ChangePasswd()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_new_passwd_not_empty:\"ERROR: New Password cannot be empty.\",\
					str_alert_pwd_too_long:\"Error! Password length too long.\",\
					str_alert_confirmed_pwd_not_empty:\"ERROR: Confirmed Password cannot be empty.\",\
					str_alert_new_defrent_confirmed_pwd:\"ERROR: New Password is not the same as Confirmed Password.\",\
					str_alert_setting_change:\"Setting has been changed.\nNeed to reboot for the value to take effect\",\
				},\
			},\
			h_diagnostic:\
			{\
				title:\"Diagnostic\",\
				innerHTML:\
				{\
					in_id_please_wait_tb:\"<img src=\"./img/tick.png\">&nbsp; Please wait.....\",\
					in_id_ping_diagnostic_tb:\"<img src=\"./img/tick.png\">&nbsp; Ping Diagnostic:\",\
					in_manPingHost:\"Ping Host\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"pingApply\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"pingClick()\">\",\
					in_id_Traceout_diagnostic_tb:\"<img src=\"./img/tick.png\">&nbsp; Traceout Diagnostic:\",\
					in_hosttraceroute:\"Traceout Host\",\
					in_id_epply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"traceroute\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"tracerouteApply()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_hostip_illegal:\"host ip is illegal!!!\",\
					str_alert_format_error:\"IP format error!\",\
				},\
			},\
			h_update:\
			{\
				title:\"Firmware Update\",\
				innerHTML:\
				{\
					in_id_update_image_tb:\"<img src=\"./img/tick.png\">&nbsp; Choose FW Image to update\",\
					in_id_status_tb:\"Status\",\
					in_id_loading_tb:\"<img id=\"img_loading\" src=\"./img/loading.gif\" width=11px height=11px style=\"display:none;\"><input type=text class=\"table_white_desc_text\" id=\"loading\" value=\"Please select the update package file\" size=60 readOnly>\",\
					in_id_update_patch_tb:\"<input type=\"radio\" name=\"formatType\" id=\"format_raw\" value=\"0\" checked >Use the RAW Format(u-boot.bin, uImage, ramdisk.ubifs and tk.gz)</br><input type=\"radio\" name=\"formatType\" id=\"format_upf\" value=\"1\">Use the Update Package Format(update_XXX.bin)\",\
					in_id_update_update_tb:\"<input type=\"button\" class=\"pbutton\" id=\"buttonUpload\" value=\"Update\" onclick=\"preFileupload();\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_update_reboot:\"Update is success\nThe board will be reboot.\",\
					str_alert_Unknown_error:\"Unknown error\",\
					str_alert_chose_update_patch:\"Please select the update package file at least one\",\
					str_alert_same_nameselect_again:\"There are files of same name, please select valid files again\",\
					str_alert_Downloading:\"Downloading... (\",\
					str_alert_update_wait:\"Update is success, wait a second...\",\
					str_alert_update_fail:\"Failed to update\",\
					str_alert_loading:\"loading\",\
					str_alert_Check_file:\"Check F/W file \",\
					str_alert_failed_check_file:\"Failed to check about F/W file\",\
					str_alert_confirm_update_file:\", please confirm the update file\",\
					str_alert_FW_file:\"F/W file \",\
					str_alert_update_block:\" update... block(\",\
					str_alert_Failed_download:\"Failed to download\",\
					str_alert_Download_update:\"Download success and continue F/W update soon\",\
					str_alert_Filename:\"Filename\",\
				}\
			},\
			h_sysreboot:\
			{\
				title:\"System Reboot\",\
				innerHTML:\
				{\
					in_id_reboot_tb:\"<img src=\"./img/tick.png\">&nbsp; System reboot is under progress\",\
					in_id_waiting_tb:\"Please wait.\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_seconds_remaining:\"seconds remaining\",\
				},				\
			},\
			h_ssysreboot:\
			{\
				title:\"System Reboot\",\
				innerHTML:\
				{\
					in_id_sys_reboot_tb:\"<img src=\"./img/tick.png\">&nbsp;Reboot the system\",\
					in_id_sys_reboot_take_time_tb:\"It takes about 45 seconds to reboot the system\",\
					in_id_apply_reboot_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Reboot\" onclick=\"rebootstart()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},\
			},\
			h_factoryreset:\
			{\
				title:\"Factory Reset\",\
				innerHTML:\
				{\
					in_id_Factory_Reset_tb:\"<img src=\"./img/tick.png\">&nbsp;  Factory Reset\",\
					in_id_reset_all_setting_tb:\"Reset all settings to factory default values\",\
					in_id_apply_tb:\"<div id=\"Status\"  ><input type=\"button\"  class=\"pbutton\" id=\"factrst-btn\" value=\"Apply\" onclick=\"factoryReset()\"></div>\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_ACK_Factory_Reset:\"Factory Reset processing, You must reload web-page after network connected.\",\
				},				\
			},\
			h_ltestatus:\
			{\
				title:\"LTE Information\",\
				innerHTML:\
				{				\
					in_id_lte_info_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE Information\",\
					in_id_FW_tb:\"FW Ver\",\
					in_id_sdk_tb:\"SDK Ver\",\
					in_id_mac_addr_tb:\"MAC Addr\",\
					in_id_IMEISV_tb:\"IMEISV\",\
					in_id_lte_status_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE Status\",\
					in_id_uicc_status_tb:\"UICC State\",\
					in_id_connect_tb:\"Connenction\",\
					in_id_pdn_model_tb:\"PDN Type\",\
					in_id_ipv4_addr_tb:\"IP v4 Address\",\
					in_id_ipv6_addr_tb:\"IP v6 Address\",\
					in_id_plmn_tb:\"PLMN Search\",\
					in_id_mcc_tb:\"MCC\",\
					in_id_mnc_tb:\"MNC\",\
					in_id_plmnselected_tb:\"PLMN Selected\",\
					in_id_cell_tb:\"Physical CELL ID\",\
					in_id_cellglobalid_tb:\"CellGlobalID\",\
					in_id_RSSI_tb:\"RSSI\",\
					in_id_RSRP_tb:\"RSRP\",\
					in_id_RSRQ1_tb:\"RSRQ\",\
					in_id_SINR1_tb:\"SINR\",\
					in_id_band_tb:\"Band\",\
					in_id_EARFCN_tb:\"EARFCN\",\
					in_id_bandwidth_tb:\"BandWidth\",\
					in_id_txpower_tb:\"TXPower\",\
					in_id_DLThr_tb:\"DLThr\",\
					in_id_servcell_tb:\"ServCellState\",\
					in_id_ULThr_tb:\"ULThr\",\
					in_id_roaming_tb:\"Roaming status\",\
					in_id_lte_Statistics_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE Statistics\",\
					in_id_RX_pacth_tb:\"Rx packets\",\
					in_id_Tx_pacth_tb:\"Tx packets\",\
					in_id_rx_tb:\"Rx bytes\",\
					in_id_tx_tb:\"Tx bytes\",\
					in_id_data_service_status_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE Data Service Status\",\
					in_id_service_status_tb:\"LTE Data Service Status\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},				\
			},\
			h_ltesetting:\
			{\
				title:\"LTE Setting\",\
				innerHTML:\
				{\
					in_id_lte_enable_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE Enable\",\
					in_id_enable_tb:\"Enable\",\
					id_close_tb:\"Off\",\
					id_open_tb:\"On\",	\
					in_id_apply_tb:\"<input type=\"button\" id=\"btnLteEna\" class=\"pbutton\" name=\"ButtonApply\" value=\"Apply\" onclick=\"lteSetEnable()\">\",\
					in_id_lte_connection_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE Connection Type\",\
					in_id_connection_type_tb:\"Connection Type\",\
					in_id_epply_tb:\"<input type=\"button\" id=\"btnPdnType\" class=\"pbutton\" name=\"ButtonApply\" value=\"Apply\" onclick=\"lteSetPdnType()\">	\",\
					in_id_IMEI_tb:\"<img src=\"./img/tick.png\">&nbsp; IMEI\",\
					in_id_IMEI1_tb:\"IMEI\",\
					in_id_imei_apply_tb:\"<input type=\"button\" id=\"btnIMEI\" class=\"pbutton\" value=\"Apply\" onclick=\"lteSetIMEI()\">\",\
					in_id_airplane_tb:\"<img src=\"./img/tick.png\">&nbsp; AIR PLANE MODE\",\
					in_id_Mode_tb:\"Mode\",\
					in_id_disable_enable_tb:\"<input type=\"radio\" name=\"airplane_mode\" value=\"0\" checked>Disable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"airplane_mode\" value=\"1\">Enable&nbsp;&nbsp;&nbsp;\",\
					in_id_appless_tb:\"<input type=\"button\" id=\"btnAirPlane\" class=\"pbutton\" value=\"Apply\" onclick=\"lteSetAirPlane()\">\",					\
					in_id_apn_management_tb:\"<img src=\"./img/tick.png\">&nbsp;  APN Profile Management\",\
					in_id_profile_tb:\"Profile\",\
					in_id_APN_Name_tb:\"APN Name\",\
					in_id_username_tb:\"UserName\",\
					in_id_pwd_tb:\"Password\",\
					in_id_ltecustomer_tb:\"<input type=\"button\" id=\"lteCustomerNewProfile\" class=\"pbutton\" value=\"New Profile\" onclick=\"lteNewProfile()\">&nbsp;&nbsp;<input type=\"button\" id=\"lteCustomerProfileDelete\" class=\"pbutton\" value=\"Delete\" onclick=\"lteProfileDelete()\">&nbsp;&nbsp;	<input type=\"button\" id=\"lteCustomerProfileApply\" class=\"pbutton\" value=\"Apply\" onclick=\"lteProfileApply()\">\",\
					in_id_NEW_Profile_tb:\"<img src=\"./img/tick.png\">&nbsp; New Profile \",\
					in_id_profile1_tb:\"Profile\",\
					in_id_apn_name1_tb:\"APN Name\",\
					in_id_username1_tb:\"UserName\",\
					in_id_pwd1_tb:\"Password\",\
					in_id_apply_cancel_tb:\"<input type=\"button\" id=\"lteNewCustomerProfileApply\" class=\"pbutton\" value=\"Apply\" onclick=\"lteNewProfileApply()\">&nbsp;&nbsp;<input type=\"button\" id=\"lteNewCustomerProfileCancel\" class=\"pbutton\" value=\"Cancel\" onclick=\"lteNewProfileCancel()\">	\",\
					in_id_plmn_search_tb:\"<img src=\"./img/tick.png\">&nbsp; PLMN Search Type\",					\
					in_id_type1_tb:\"Type\",\
					in_id_PLMN_search3_tb:\"PLMN search\",\
					in_id_PLMN_search_Ext_tb:\"PLMN search Extension\",\
					in_id_apples_tb:\"<input type=\"button\" id=\"btnPlmnSearchType\" class=\"pbutton\" value=\"Apply\" onclick=\"lteSetPlmnSearchType()\">\",\
					in_id_plmn_search1_tb:\"<img src=\"./img/tick.png\">&nbsp;   PLMN Search Extension Info\",\
					in_id_search_type_tb:\"Selection Mode\",\
					in_id_auto_tb:\"Automatic network selection\",\
					in_id_manual_tb:\"Manual network selection\",\
					in_btnManualPlmnSearching:\"Search\",\
					in_id_search_mode_tb:\"Operation Mode\",\
					in_id_normal_tb:\"Normal searching\",\
					in_id_emergency_tb:\"Emergency searching\",\
					in_id_Roaming_tb:\"Roaming Option\",\
					in_id_enable1_tb:\"Allowed\",\
					in_id_refuse_tb:\"Not allowed\",\
					in_id_Searching_Type_tb:\"Searching Type\",\
					in_id_searching_type1_tb:\"<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"0\">MRU Search<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"1\">EARFCN<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"2\">Band	<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"3\">EARFCN Range&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" class=\"pbutton\" id=\"btnPlmnExtSearchingTypeAdd\" value=\"Add\" style=\"width:50px; align:right\" onclick=\"plmn_ext_searching_type_add()\">\",\
					in_btnPlmnExtSearchingTypeAdd:\"Add\",\
					in_id_Type2_tb:\"Type\",\
					in_id_num_of_value_tb:\"Num of Value\",\
					in_id_value_tb:\"Value\",\
					in_id_NetListTable_tb:\"<img src=\"./img/tick.png\">&nbsp; NetListTable\",\
					in_id_operator_name_tb:\"OperatorName\",\
					in_id_operator_code_tb:\"OperatorCode\",\
					in_id_status_tb:\"Status\",\
					in_id_type3_tb:\"Type\",\
					in_id_eppli_tb:\"<input type=\"button\" id=\"btnPlmnExt\" class=\"pbutton\" value=\"Apply\" onclick=\"lteSetPlmnExt()\">	\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_IMEI_length:\"IMEI length should be 15.\",\
					str_alert_IMEI_invalid:\"IMEI is invalid. Please check again.\",\
					str_alert_PLMNID:\"Error : Wrong PLMN ID, PLMNID should be a combination of numeric values.\",\
					str_alert_PLMNID_length:\"Error : PLMN ID is invalid.\n The length of PLMNID is 5 or 6.\",\
					str_alert_board_reboot:\"\nThe board will be reboot.\",\
					str_alert_save_reboot_effect:\"Saving IMEI done.\nNeed to reboot for the values to take effect\",\
					str_alert_air_plan_mode:\"Set Air Plane Mode.\",\
					str_alert_UE_mode:\"Set UE Mode.\",\
					str_alert_sav_PLMN_Searcy:\"Saving PLMN Searcy Type done\",\
					str_alert_Invalid_value:\"Invalid ECI value!\",\
					str_alert_Searching_lists:\"Too many Searching type lists.(\",\
					str_alert_max_num_6:\") (Number of MAX : 6)\",\
					str_alert_Manual_CSG:\"Manual CSG selection mode is not supported\",\
					str_alert_fill_blanks:\"Please fill in the blanks..\",\
					str_alert_out_maximum:\"The data size is out of the maximum(255).:  \",\
					str_alert_plmn_info:\"Saving PLMN Search Extension Information done.\",\
					str_alert_save_APN:\"Saving APN table done\",\
					str_alert_save_jiange_done:\"Saving Search Interval done\",\
					str_alert_save_IMS_PCAP_reboot_effect:\"Saving IMS PCAP Setting done.\nNeed to reboot for the values to take effect\",\
					str_alert_num_max_10:\" (Number of MAX : 10)\",\
					str_alert_invalid_value1:\"Invalid number of value:\",\
					str_alert_num_max_16:\"(Number of MAX : 16)\",\
					str_alert_num_max_5:\"(Number of MAX : 5)\",\
					str_alert_searching_type1:\"Select Searching Type\",\
					str_alert_plmn_search_item:\"Can't support plmn search extension no more items.\",\
					str_alert_EMM_timer:\"Set EMM Timer.\",\
					str_alert_PSM_timer:\"Set PSM Mode and Timer.\",\
					str_alert_location_service:\"Set Location Service Option.\",\
					str_alert_apntble:\"apntble is null\",\
					str_alert_APN_using:\"APN is using!\",\
					str_alert_APN_table:\"Saving APN table done\",\
					str_alert_reboot:\"The board will be reboot.\",\
					str_alert_profile_null:\"profile is NUll\",\
					str_alert_apn_name:\"apn name is NUll\",\
					str_alert_apn_num_full:\"apn Num is full!\",\
					str_alert_MRU_count:\"MRU Count\",\
					str_alert_EARFCN:\"EARFCN\",\
					str_alert_Band:\"Band\",\
					str_alert_EARFCN_Range:\"EARFCN Range\",\
					str_alert_delete:\"' value='Delete' style='width:50px;' onclick='plmn_ext_searching_type_delete()'>\",\
					str_alert_Manual_plmn:\"Manual plmn search ok!\",\
					str_alert_After_setting:\"After setting the board will be reboot.\nDo you want to continue?\",\
					str_alert_connection_lost:\"After setting the connection will be lost.\nDo you want to continue?\",\
				}\
			},\
			h_sim_pin:\
			{\
				title:\"LTE SIM PIN\",\
				innerHTML:\
				{				\
					in_id_pin_info_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN Information\",\
					in_id_pin_sta_tb:\"PIN Status\",\
					in_id_retries_pin_tb:\"RETRIES PIN\",\
					in_id_retries_puk_tb:\"RETRIES PUK\",\
					in_id_refresh_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_REFRESH\" value=\"Refresh\" onclick=\"getPinStatus()\">\",\
					in_id_pin_management_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN Management\",\
					in_id_pin_code_tb:\"PIN Code\",\
					in_id_enablePin_disable_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_VERIFY\" value=\"Verify\" onclick=\"verifyPin()\"><input type=\"button\" class=\"pbutton\" id=\"BTN_ENABLE\" value=\"Enable\" onclick=\"enablePin()\"><input type=\"button\" class=\"pbutton\" id=\"BTN_DISABLE\" value=\"Disable\" onclick=\"disablePin()\">\",\
					in_id_pin_change_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN Change\",\
					in_id_pin_code1_tb:\"PIN Code\",\
					in_id_new_pin_code_tb:\"New PIN Code\",\
					in_id_confirm_pin_code_tb:\"Confirm New PIN Code\",\
					in_id_changepin_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_CHANGE\" value=\"Change\" onclick=\"changePin()\">\",\
					in_id_pin_unblock_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN Unblock\",\
					in_id_puk_code_tb:\"PUK Code\",\
					in_id_new_pin_code1_tb:\"New PIN Code\",\
					in_id_unlock1_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_UNBLOCK\" value=\"Unblock\" onclick=\"unblockPin()\">\",\
					in_id_sim_lock_tb:\"<img src=\"./img/tick.png\">&nbsp; SIM Lock\",\
					in_id_sim_lock1_tb:\"SIM Lock\",\
					in_id_unlock_tb:\"Unlock\",\
					in_id_lock_tb:\"Lock\",\
					in_id_eppli_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_SIM_LOCK\" value=\"Apply\" onclick=\"lockSIM()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_verify_fail:\"Verify FAIL\",\
					str_alert_Verify_OK:\"Verify OK\",\
					str_alert_enable_fail:\"Enable FAIL\",\
					str_alert_enable_ok:\"Enable OK\",\
					str_alert_disable_fail:\"Disable FAIL\",\
					str_alert_disable_ok:\"Disable OK\",\
					str_alert_incorrect_new_pin:\"Incorrect NEW PIN\",\
					str_alert_change_fail:\"Change FAIL\",\
					str_alert_change_ok:\"Change OK\",\
					str_alert_unblock_fail:\"Unblock FAIL\",\
					str_alert_unblock_ok:\"Unblock OK\",\
					str_alert_lock_unlock:\"Lock/Unlock SIM OK!\",\
					str_alert_reboot:\"\nThe board will be reboot.\",\
					str_alert_locked_status:\"SIM is locked status!\",\
					str_alert_unlocked_status:\"SIM is unlocked status!\",\
				},				\
			},\
			h_ltesms:\
			{\
				//title:\"SMS Send/Receive\",\
				innerHTML:\
				{			\
					in_id_title_tb:\" SMS Send/Receive\",\
					in_id_conf_tb:\"<img src=\"./img/tick.png\">&nbsp;  Configuration\",\
					in_id_sms_mo_format_tb:\"SSMS MO Format\",\
					in_id_Storage_tb:\"Storage\",\
					in_id_ims_test_tb:\"IMS Test Mode\",\
					in_id_disable_tb:\"Disabled\",\
					in_id_enable_tb:\"Enabled\",\
					in_id_disable1_tb:\"Disabled\",\
					in_id_enable1_tb:\"Enabled\",\
					in_id_eppli_tb:\"<input type=\"button\" id=\"btnConfig\" class=\"pbutton\" name=\"ConfigApply\" value=\"Apply\" onclick=\"setSMSConfig()\">\",\
					in_id_sms_status_tb:\"<img src=\"./img/tick.png\">&nbsp; SMS Status\",\
					in_id_nv_info_tb:\"NV Message\",\
					in_id_uicc_info_tb:\"UICC Message\",\
					in_id_SCA_tb:\"SCA\",\
					in_id_apply_tb:\"<input type=\"button\" id=\"btnSaveSCA\" class=\"pbutton\" value=\"Apply\" onclick=\"setSCA()\">\",\
					in_id_epply_tb:\"<input type=\"button\" id=\"btnSavePSISMSC\" class=\"pbutton\" value=\"Apply\" onclick=\"setPSISMSC()\">\",\
					in_id_user_psismsc_tb:\"User PSISMSC\",\
					in_id_eppli1_tb:\"<input type=\"button\" id=\"btnSaveUserPSISMSC\" class=\"pbutton\" value=\"Apply\" onclick=\"setUserPSISMSC()\">\",\
					in_id_sms_info_tb:\"<img src=\"./img/tick.png\">&nbsp; SMS Message\",\
					in_id_recive_info_tb:\"Receive Message\",\
					in_id_format_tb:\"Format\",\
					in_id_document_tb:\"TEXT 3GPP2\",\
					in_id_document1_tb:\"TEXT 3GPP\",\
					in_id_storage_tb:\"Storage\",\
					in_id_Filter_tb:\"Filter\",\
					in_id_all_tb:\"ALL\",\
					in_id_unread_tb:\"UNREAD\",\
					in_id_read_tb:\"READ\",\
					in_id_unsent_tb:\"UNSENT\",\
					in_id_sent_tb:\"SENT\",\
					in_id_refresh_tb:\"<input type=\"button\" id=\"btnRefreshSMS\" class=\"pbutton\" style=\"width:120px\" value=\"Refresh\" onclick=\"RefreshReceiveSMS()\">\",\
					in_id_index_tb:\"IDX\",\
					in_id_Priority_tb:\"Priority\",\
					in_id_storage1_tb:\"Storage\",\
					in_id_direction_tb:\"Direction\",\
					in_id_type_tb:\"Type\",\
					in_id_time_tb:\"Time\",\
					in_id_info_tb:\"Message\",\
					in_id_delete_msg_tb:\"Delete Message\",\
					in_id_index1_tb:\"INDEX\",\
					in_id_read1_tb:\"READ\",\
					in_id_sent1_tb:\"SENT\",\
					in_id_read_sent_unsent_tb:\"READ_SENT_UNSENT\",\
					in_id_all1_tb:\"ALL\",\
					in_id_delete_tb:\"<input type=\"button\" id=\"btnDeleteSMS\" class=\"pbutton\" style=\"width:120px\" value=\"Delete\" onclick=\"DeleteSMS()\">\",\
					in_id_sent_msg_tb:\"Send Message\",\
					in_id_format1_tb:\"Format\",\
					in_id_first_tb:\"Priority\",\
					in_id_normal_tb:\"Normal\",\
					in_id_Interactive_tb:\"Interactive\",\
					in_id_urgent_tb:\"Urgent\",\
					in_id_emergency_tb:\"Emegency\",\
					in_id_privacy_tb:\"Privacy\",\
					in_id_no_Restricted_tb:\"NOT Restricted\",\
					in_id_restricted_tb:\"Restricted\",\
					in_id_Confidential_tb:\"Confidential\",\
					in_id_secret_tb:\"Secret\",\
					in_id_Alert_tb:\"Alert\",\
					in_id_default_tb:\"Default\",\
					in_id_low_tb:\"Low\",\
					in_id_medium_tb:\"Medium\",\
					in_id_high_tb:\"High\",\
					in_id_char_set_tb:\"Character Set(GSM/ASCII)\",\
					in_id_reply_tb:\"Reply\",\
					in_sms_reply_user:\"User\",\
					in_sms_reply_delivery:\"Delivery\",\
					in_sms_reply_read:\"Read\",\
					in_sms_reply_report:\"Report\",\
					in_id_info1_tb:\"Message\",\
					in_id_direction2_tb:\"To\",\
					in_id_format1_tb:\"CB\",\
					in_id_storage2_tb:\"Temporary Store\",\
					in_id_senta_tb:\"<input type=\"button\" id=\"btnSendSMS\" class=\"pbutton\" style=\"width:120px\" value=\"Send\" onclick=\"SendSMS()\">\",\
					in_loadingDiv:\"	Please wait..\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_Retry_finished:\"\nRetry finished\n\",\
				str_alert_ACK_Success:\"SMS Delivery ACK Success\",\
				str_alert_ACK_NO_action:\"SMS Delivery ACK NO action\",\
				str_alert_sca_conf:\"Save SCA Configuration.\",\
				str_alert_psismsc_conf:\"Save PSISMSC Configuration.\",\
				str_alert_save_psismsc_conf:\"Save User PSISMSC Configuration.\",\
				str_alert_save_sms_reboot:\"Save SMS Configuration.\nThe board will be reboot.\",\
				str_alert_get_sms_conf:\"Get SMS IMS Configuration.\",\
				str_alert_sms_sending:\"\nRetry SMS Sending.\nAfter 20 sec\",\
				str_alert_result:\"\nFAIL SMS\nResult :\",\
				str_alert_sms_send_fail:\"\nSMS Send fail.\n\",\
				str_alert_sms_sending_20:\"\nRetry SMS Sending.\nAfter 20 sec\n\",\
				str_alert_sms_fail:\"\nSMS Send fail.\n\",\
				str_alert_sms_cause:\"\nSMS Result Cause : \",\
				str_alert_sms_fail_no_reply:\"\nSMS Send fail.\nNo response.\",\
				str_alert_sms_send_ok:\"SMS Delivery ACK Success\",\
				str_alert_SMS_content:\"Select SMS content\",\
				str_alert_delete_reload_list:\"SMS deleted, reloading the list\",		\
				str_alert_sms_refresh_ok:\"Sms refresh OK!\",\
				},				\
			},\
			h_wifistatus:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_title_tb:\"WiFi Information\",\
					in_id_wifi_status_tb:\"<img src=\"./img/tick.png\">&nbsp; WiFi Status\",\
					in_id_ap_instance_tb:\"AP Instance\",\
					in_id_network_name_tb:\"Network Name (SSID)\",\
					in_id_network_mode_tb:\"Network Mode\",\
					in_id_rx_packets_tb:\"Rx Packets\",\
					in_id_tx_packets_tb:\"Tx Packets\",\
					in_id_RX_Byte_tb:\"Rx Bytes\",\
					in_tx_byte_tb:\"Tx Bytes\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_cannot_find_enabled_ap_setting_page:\"Cannot find Enabled AP.\n please create AP in AP Setting Page.\",\
				},	\
			},\
			h_wificommon:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_wifi_settig_tb:\"WiFi Setting\",\
					in_id_common_setting_tb:\"<img src=\"./img/tick.png\">&nbsp; Common Setting\",\
					in_id_Freqency_channel_tb:\"Frequency (Channel)\",\
					in_id_auto_tb:\"Auto\",\
					in_id_tx_power_tb:\"TX Power\",\
					in_id_beacon_interval_tb:\"Beacon Interval\",\
					in_id_preamble_tb:\"Preamble\",\
					in_id_long_tb:\"Long\",\
					in_id_short_tb:\"Short\",\
					in_id_apply_tb:\"<input type=\"button\" id=\"btnwificommon\" class=\"pbutton\" value=\"Apply\" onclick=\"wifiSetCommon()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_wifi_setting_change_ok:\"Wifi setting changed successfully\n\",\
				},\
			},\
			h_wifisetting:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_wifi_setting_tb:\"WiFi Setting\",\
					in_id_AP_Enable_tb:\"<img src=\"./img/tick.png\">&nbsp; AP Enable:\",\
					in_id_enable_tb:\"Enable\",\
					in_id_disable_enable_tb:\"<input type=\"radio\" name=\"autoexec\" value=\"0\" >Disable&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"autoexec\" value=\"1\">Enable&nbsp;&nbsp;&nbsp;\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"ap_enable_switch\" value=\"Apply\" onclick=\"EnableAP()\">\",\
					in_id_ap_setting1_tb:\"<img src=\"./img/tick.png\">&nbsp; AP Setting\",\
					in_id_start_wlan_tb:\"Start wlan\",\
					in_id_wps_enable_tb:\"WPS Enable\",\
					in_id_disable1_tb:\"Disable\",\
					in_id_enable1_tb:\"Enable\",\
					in_id_Network_name_tb:\"Network Name (SSID)\",\
					in_id_Network_mode_tb:\"Network Mode\",\
					in_id_Frequency_Band_tb:\"Frequency Band\",\
					in_id_Max_No_station_tb:\"Max No. of station\",\
					in_id_Hidden_ssid_tb:\"Hidden SSID\",\
					in_id_Off_tb:\"Off\",\
					in_id_On_tb:\"On\",\
					in_id_authentication_tb:\"Authentication\",\
					in_id_encryption_tb:\"Encryption\",\
					in_id_network_key_tb:\"Network Key\",\
					in_id_key_Type_tb:\"Key Type\",\
					in_id_index_to_use_tb:\"Index to use\",\
					in_id_input_key_tb:\"Please input the key\",\
					in_id_appli_tb:\"<input type=\"button\" id=\"btnwifiSet\" class=\"pbutton\" value=\"Apply\" onclick=\"wifiSetSetting()\">\",\
					in_id_ap_list_tb:\"<img src=\"./img/tick.png\">&nbsp; AP List\",\
					in_id_instance_tb:\"Instance\",\
					in_id_RF_Mode_tb:\"RF Mode\",\
					in_id_encrytion_tb:\"Encrytion\",\
					in_id_add_ap_tb:\"<input type=\"button\" id=\"btnwifiAdd\" class=\"pbutton\" value=\"Add AP\" onclick=\"addAPToList()\">\",\
					in_id_eppli_tb:\"<input type=\"button\" id=\"btnAPListApply\" class=\"pbutton\" value=\"Apply\" onclick=\"wifiRestartApd()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_instance_select_11ac:\"Only one instance can select 11ac. Please check again.\",\
				str_alert_add_new_ap_instance:\"Please add to new AP instance.\",\
				str_alert_not_matching_index:\"Not Matching Key Index\n Please input Key\",\
				str_alert_error:\"Error\",\
				str_alert_change1_success:\"Wifi setting changed successfully\",\
				str_alert_change_success:\"Wifi setting changed successfully\nNeed to restart for the changes to take effect\",\
				str_alert_restart:\"Wifi AP is restarted\",\
				str_alert_cannot_support_ap_instance:\"Cannot add new AP instance, because not yet support 3 AP instance.\",\
				str_alert_cannot_support_multiple:\"Cannot add new AP instance, because not yet support multiple AP instance.\",\
				str_alert_ap_added_reloading:\"AP added, reloading the list\",\
				str_alert_startPBC_seccess:\"Start PBC successfully!  You have to run Wi-Fi Protected Setup within 2 minutes.\",\
				str_alert_pin_is_null:\"PIN is NULL\",\
				str_alert_apply_wpspin_successfully:\"Applied WPS PIN successfully! You have to run Wi-Fi Protected Setup within 2 minutes.\",\
				str_alert_wps_ap_invaild:\"WPS AP PIN is invaild\",\
				str_alert_wifi_setting_change:\"Wifi setting changed successfully\",\
				str_alert_Remove:\"Remove\",\
				},\
			},\
			h_syslog:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_sys_logtitle_tb:\"System Log\",\
					in_id_sys_log:\"<img src=\"./img/tick.png\">&nbsp;System Log Mask\",\
					in_id_default_Manual_tb:\"Default/Manual\",\
					in_id_default_tb:\"Default\",\
					in_id_Manual_tb:\"Manual\",\
					in_id_log_mask_tb:\"Log Mask\",\
					in_id_tag_tb:\"Tag\",\
					in_id_Description_tb:\"Description\",\
					in_id_use_tb:\"Use\",\
					in_id_level_tb:\"Level\",\
					in_id_add_tag_tb:\"Add Tag\",\
					in_id_add_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Add\" onclick=\"onClickAddLogMask();\">\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Apply\" onclick=\"onClickApplyLogMask()\">\",\
					in_id_sys_log_save_tb:\"<img src=\"./img/tick.png\">&nbsp; System Log Save\",\
					in_id_disable_enable_tb:\"<input type=\"radio\" name=\"logsave\" id=\"nand\" value=\"0\" checked >disable&nbsp;<input type=\"radio\" name=\"logsave\" id=\"dram\" value=\"1\">enable&nbsp;\",\
					in_id_appli_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BtnSetLogSave\" value=\"Apply\" onclick=\"SetLoggingType()\">\",\
					in_id_add_dm_tb:\"<img src=\"./img/tick.png\">&nbsp; Add DM Command to Booting Script\",\
					in_id_enable_log_tb:\"Q Log\",\
					in_id_enable_desable_tb:\"<input type=\"radio\" name=\"q_log\" id=\"q_log_disable\" value=\"0\">disable<input type=\"radio\" name=\"q_log\" id=\"q_log_enable\" value=\"1\">enable\",\
					in_id_lte_log_locate_tb:\"LTE Log Location\",\
					in_armlog_uart:\"<input type=\"radio\" name=\"arm1log\" id=\"armlog_uart\" value=\"1\">UART<input type=\"radio\" name=\"arm1log\" id=\"arm1log_lted_cli\" value=\"2\">BUFFER<input type=\"radio\" name=\"arm1log\" id=\"arm1log_file\" value=\"3\">FILE\",\
					in_id_init_dm_tb:\"Initial DM Commands\",\
					in_id_applie_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Apply\" onclick=\"setScript()\">\",\
					in_id_download_log_tb:\"<img src=\"./img/tick.png\">&nbsp;  Download Log File\",\
					in_id_file_name_tb:\"file name\",\
					in_id_reboot_tb:\"<input type=\"button\" class=\"pbutton\" title=\"Download\" value=\"Reset\" onclick=\"resetLogFile('all')\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_setting_change_reboot:\"Setting has been changed.\nNeed to reboot for Saving System debugging log\",\
				str_alert_tag_name_null:\"Tag name is none!\",\
				str_alert_tag_name_exist:\"Inputted tag name already exists!\",\
				str_alert_save_log_done_reboot:\"Saving Log mask done.\nNeed to reboot for the values to take effect\",\
				str_alert_save_DM_reboot:\"Saving DM Command done.\nNeed to reboot for the values to take effect\",\
				str_alert_down_load:\"<input type='button' class='pbutton' title='Download' value='Download'>\",\
				str_alert_delete:\"<input type='button' class='pbutton' title='Delete' value='Delete' onClick='resetLogFile(\"\",\
				},\
			},\
			h_left:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_system1:\"System\",\
					in_id_system21:\"Status\",\
					in_id_system22:\"Network\",\
					in_id_system222:\"Network\",\
					in_id_system23:\"Connection Management\",\
					in_id_portforwarding:\"NAT/Router Manager\",\
					in_id_tr069:\"TR069\",\
					in_id_ntp:\"NTP\",\
					in_id_user:\"USER\",\
					in_id_diagnostic:\"Diagnostic\",\
					in_id_system24:\"Firmware Update\",\
					in_id_system25:\"Factory Reset\",\
					in_id_system27:\"Reboot\",\
					in_id_system28:\"System Language\",\
					in_id_lte1:\"LTE\",\
					in_id_lte21:\"Status\",\
					in_id_ltesetting1:\"Setting\",\
					in_id_ltesetting2:\"Setting\",\
					in_id_lte24:\"SIM PIN\",\
					in_id_lte25:\"SMS\",\
					in_id_volte:\"VoLTE\",\
					in_id_lte26:\"OTA-DM\",\
					in_id_lteplmncsg:\"PLMN CSG\",\
					in_id_wifiap1:\"WiFi\",\
					in_id_wifiap21:\"AP Status\",\
					in_id_wifiap22:\"AP Common\",\
					in_id_wifiap23:\"AP Setting\",\
					in_id_wifiap24:\"AP Access Control\",\
					in_id_wifiap25:\"AP WPS Setting\",\
					in_id_wifista26:\"STA Setting\",\
					in_id_engineer1:\"Engineering\",\
					in_id_engineer24:\"File Upload\",\
					in_id_engwimaxnv:\"NV-Wimax\",\
					in_id_engltenv:\"NV-LTE\",\
					in_id_engcommonnv:\"NV-Common\",\
					in_id_englog:\"Log\",\
					in_id_Expand:\"Expand\",\
					in_id_Collapse:\"Collapse\"\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_tag_name1_null:\"Tag name is none!\"\
				},\
			},\
			h_syslanguage:\
			{\
				title:\"PON Banner\",\
				innerHTML:\
				{\
					in_id_language_tb:\"<img src=\"./img/tick.png\">&nbsp; LANGUAGE:\",\
					in_id_language_transformation_tb:\"language transformation\",\
					in_id_ch_en_tb:\"<input type=\"radio\" name=\"autoexec\" value=\"0\" >English&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"autoexec\" value=\"1\">Chinese&nbsp;&nbsp;&nbsp;\",\
					in_id_epplie_tb:\"<input type=\"button\" class=\"pbutton\" id=\"language_enable_switch\" value=\"Apply\" onclick=\"Enablelanguage()\">\",\
					in_id_enable_tb:\"Enable\"\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_seting_changed:\"Setting has been changed.\n.\",\
				},	\
			},			\
			h_mac_pop:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_connect_mac_tb:\"<img src=\"./img/tick.png\">&nbsp; Connected MAC List\",\
					in_id_no_tb:\"No.&nbsp;\",\
					in_id_ipaddr_tb:\"Ip address\",\
					in_id_mac_addr_tb:\"Mac address\",\
					in_id_link_time_tb:\"Link time\",\
					in_id_appli_cancel_tb:\"<input type=\"button\" class=\"pbutton\" name=\"Apply\" value=\"Apply\" onclick=\"returnParsed()\"><input type=\"button\" class=\"pbutton\" name=\"Cancel\" value=\"Cancel\" onclick=\"window.close()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_check_any_one:\"you should check any one.\",\
						str_alert_mac_addr_done:\"Mac address set completion.\nplease push Add button.\",\
				},				\
			},\
			h_home:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_Reference_tb:\"CPE Reference Web\",	\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},				\
			},\
			h_cm:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_cm_tb:\"Connection Manager\",				\
					in_id_RF_tb:\"<img src=\"./img/tick.png\">&nbsp; RF Interfaces\",\
					in_id_up_down_tb:\"Up / Down\",\
					in_id_priority_tb:\"Priority\",\
					in_id_name_tb:\"Name\",\
					in_id_enable_tb:\"Enable\",\
					in_id_status_tb:\"State\",\
					in_id_appplies_tb:\"<input type=\"button\" class=\"pbutton\" id=\"btnPriority\" name=\"ButtonApply\" value=\"Apply\" onclick=\"setPriority()\">	\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_no_change_priority:\"No need to change the priority\",\
					str_alert_top_priority:\"Already is the top priority\",\
					str_alert_lowest_priority:\"Already is the lowest priority\",\
					str_alert_up:\"Up\",\
					str_alert_down:\"Down\",\
					str_alert_on:\"On\",\
					str_alert_off:\"Off\",\
					str_alert_setting_change_reboot1:\"Setting has been changed.\nNeed to reboot for the values to take effect\",\
				},\
			},\
			h_VoLTE:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_Vo_Set_tb:\"VoLTE Setting\",		\
					in_id_setting_tb:\"<img src=\"./img/tick.png\">&nbsp; Setting\",\
					in_id_enable_tb:\"Enable\",\
					in_id_off_tb:\"Off\",\
					in_id_on_tb:\"On\",\
					in_id_session_timer_tb:\"Session Timer IMS\",\
					in_id_sec_tb:\"<input type=\"text\" class=\"inputtext\" id=\"session_timer_ims\" style=\"width:150\">&nbsp;sec\",\
					in_id_sec1_tb:\"<input type=\"text\" class=\"inputtext\" id=\"min_se_ims\" style=\"width:150\">&nbsp;sec\",\
					in_id_on_off1_tb:\"	<input type=\"radio\" name=\"amrwb_mode\" value=\"0\">OFF&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"amrwb_mode\" value=\"1\">ON\",\
					in_id_on_off2_tb:\"<input type=\"radio\" name=\"scr_amr_mode\" value=\"0\">OFF&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"scr_amr_mode\" value=\"1\">ON\",\
					in_id_on_off3_tb:\"<input type=\"radio\" name=\"scr_amrwb_mode\" value=\"0\">OFF&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"scr_amrwb_mode\" value=\"1\">ON\",\
					in_id_ring_tb:\"<span id=\"tb_0700\">Ringing Timer IMS</span>\",\
					in_id_sec2_tb:\"<input type=\"text\" class=\"inputtext\" id=\"ringing_timer_ims\" style=\"width:150\">&nbsp;sec\",\
					in_id_ringback_tb:\"Ringback Timer IMS\",\
					in_id_sec3_tb:\"<input type=\"text\" class=\"inputtext\" id=\"ringback_timer_ims\" style=\"width:150\">&nbsp;sec\",\
					in_id_RTP_RTCP_tb:\"RTP RTCP Inactivity Timer IMS\",\
					in_id_sec4_tb:\"<input type=\"text\" class=\"inputtext\" id=\"rtp_rtcp_inactivity_timer_ims\" style=\"width:150\">&nbsp;sec\",\
					in_id_UDP_tb:\"<span id=\"tb_1000\">UDP Keep Alive</span>\",\
					in_id_sec5_tb:\"<input type=\"text\" class=\"inputtext\" id=\"udp_keep_alive\" style=\"width:150\">&nbsp;sec\",\
					in_id_T1_Timer_tb:\"T1 Timer IMS\",	\
					in_id_sec6_tb:\"<input type=\"text\" class=\"inputtext\" id=\"t1_timer_ims\" style=\"width:150\">&nbsp;sec\",	\
					in_id_T2_Timer_tb:\"T2 Timer IMS\",	\
					in_id_sec7_tb:\"<input type=\"text\" class=\"inputtext\" id=\"t2_timer_ims\" style=\"width:150\">&nbsp;sec\",	\
					in_id_TF_IMS_tb:\"TF Timer IMS\",\
					in_id_sec8_tb:\"<input type=\"text\" class=\"inputtext\" id=\"tf_timer_ims\" style=\"width:150\">&nbsp;sec\",	\
					in_id_tty_tb:\"<span id=\"tb_1400\">TTY Mode</span>\",	\
					in_id_CHO_VCO_tb:\"<input type=\"radio\" name=\"TTY_mode\" value=\"0\" checked>OFF&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"TTY_mode\" value=\"1\" >HCO&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"TTY_mode\" value=\"2\">VCO&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"TTY_mode\" value=\"3\">FULL\",	\
					in_id_pcmu_tb:\"<span id=\"tb_1500\">Pcmu Enable</span>\",\
					in_id_enable_disable_tb:\"<input type=\"radio\" name=\"pcmuenable_mode\" value=\"0\" checked>Disable&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"pcmuenable_mode\" value=\"1\" >Enable\",	\
					in_id_confserv_tb:\"<span id=\"tb_1600\">Confserv URL</span>\",	\
					in_id_all_reboot_tb:\"<input type=\"button\" id=\"applybutton\" class=\"pbutton\" value=\"All Apply  &  Reboot\" onclick=\"set_volte_setting()\" style=\"width:600\">\",						\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_Session_Timer:\"Session Timer IMS Range : 90 ~ 7200\",\
					str_alert_Min_Se:\"Min Se IMS Range : 90 ~ 3600\",\
					str_alert_RTP_RTCP:\"RTP RTCP Inactivity Timer IMS Range : 10 ~300\",\
					str_alert_board_reboot:\"After setting the board will be reboot.\nDo you want to continue?\",\
				},				\
			},\
			h_otadm:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{			\
					in_defer_download_dialog:\"<p>When do you want to download this update?</p>\",	\
					in_defer_update_dialog:\"<p>When do you want to update this update?</p>\",	\
					in_download_dialog_mandatory:\"<p>Do you want to download firmware package?</p>\",\
					in_download_dialog_optional:\"<p>Do you want to download firmware package?</p>\",\
					in_update_dialog_optional:\"<p>Do you want to update firmware package?</p>\",\
					in_update_success_dialog:\"<p>Restart your IMG03 to complete the installation.<br>Your IMG03 will take about 3 minutes to restart.</p>\",\
					in_loadingDiv:\"Please wait..\",\
					in_id_lte_fota_test_tb:\"LTE FOTA Test Page\",	\
					in_id_info_tb:\"<img src=\"./img/tick.png\">&nbsp; Information\",	\
					in_id_current_status_tb:\"Current Status\",	\
					in_id_operation_tb:\"<img src=\"./img/tick.png\">&nbsp; Operation\",\
					in_id_check_again_tb:\"Check New S/W Package\",\
					in_id_check_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_CHECK_NEW_SW\" value=\"Check\" onclick=\"runOtaDmCheckForNewSU()\" style=\"width:150px\">\",\
					in_id_server_tb:\"OTA DM Server Setting <br/>(Only for IOT IOT)\",\
					in_id_server_ip_tb:\"Server Address <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SERVER_ADDR\" style=\"width:200px\">\",\
					in_id_set_get1_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_SERVER_ADDR\" value=\"Get\" onclick=\"getOtaDmInfo(0)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_SERVER_ADDR\" value=\"Set\" onclick=\"setOtaDmInfo(0)\" style=\"width:70px\">\",\
					in_id_server_port_tb:\"Server Port <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SERVER_PORT\" style=\"width:200px\">\",					\
					in_id_get_set2_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_SERVER_PORT\" value=\"Get\" onclick=\"getOtaDmInfo(1)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_SERVER_PORT\" value=\"Set\" onclick=\"setOtaDmInfo(1)\" style=\"width:70px\">\",\
					in_server_ip_type_tb:\"Server Addr Type  <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SERVER_ADDR_TYPE\" style=\"width:200px\">\",	\
					in_id_get_set3_tb:\"	<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_SERVER_ADDR_TYPE\" value=\"Get\" onclick=\"getOtaDmInfo(2)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_SERVER_ADDR_TYPE\" value=\"Set\" onclick=\"setOtaDmInfo(2)\" style=\"width:70px\">\",\
					in_id_sw_tb:\"	SW Version <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SW_VERSION\" style=\"width:200px\">\",\
					in_id_get_set4_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_SW_VERSION\" value=\"Get\" onclick=\"getOtaDmInfo(3)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_SW_VERSION\" value=\"Set\" onclick=\"setOtaDmInfo(3)\" style=\"width:70px\">\",\
					in_id_FW_version_tb:\"FW Version <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_FW_VERSION\" style=\"width:200px\">\",\
					in_id_get_set5_tb:\"	<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_FW_VERSION\" value=\"Get\" onclick=\"getOtaDmInfo(4)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_FW_VERSION\" value=\"Set\" onclick=\"setOtaDmInfo(4)\" style=\"width:70px\">\",\
					in_id_HW_version_tb:\"HW Version <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_HW_VERSION\" style=\"width:200px\">\",\
					in_id_get_set_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_HW_VERSION\" value=\"Get\" onclick=\"getOtaDmInfo(5)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_HW_VERSION\" value=\"Set\" onclick=\"setOtaDmInfo(5)\" style=\"width:70px\">\",					\
					in_id_non_interaction_mode_tb:\"Non-interaction Mode\",	\
					in_id_non_usb_mode_tb:\"<div id=\"TXT_NONINTERACTION_MODE\" >Non-USB mode</div>\",	\
					in_id_on_off_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_INTERACTION_MODE\" value=\"Switch\" onclick=\"runNoninteracionMode()\" style=\"width:150px\">\",\
					in_id_OTA_NV_tb:\"OTA NV Reset\",\
					in_id_reset_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_OTA_NV_RESET\" value=\"Reset\" onclick=\"runOtaNvReset()\" style=\"width:150px\">\",\
				\},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_SW_available:\"New SW update is not available\",\
					str_alert_OTA_DM:\"Failed to get OTA-DM Status\",\
					str_alert_OTA_session:\"OTA session is already running\nPlease try again later\",\
					str_alert_storage_space:\"It will clean up all storage space for OTA-DM/FOTA.\nIt deserves to be executed only one time at OOB state.\nIMG03 will be turned off and on again.\",\
					str_alert_send_success:\"Success send result\",\
					str_alert_send_fail:\"Failed to send result, plase try again later\",\
					str_alert_get:\"Get the\",\
					str_alert_info:\"info was successful\",\
					str_alert_fail_get:\"Failed to get the\",\
					str_alert_info1:\"Info\",\
					str_alert_success:\"Success\",\
					str_alert_fail_set:\"Failed to set the\",\
					str_alert_info2:\"Failed to set the\",\
				},\
			},\
			h_plmncsg:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_PLMN_CSG1_tb:\"CPE PLMN CSG\",\
					in_id_PLMN_CSG_list_tb:\"<img src=\"./img/tick.png\"> PLMN CSG List\",\
					in_id_request1_tb:\"<input type=\"button\" id=\"btnList\" class=\"pbutton\" value=\"Request\" onClick=\"plmnCSGList()\">\",\
					in_id_plmn_csg2_tb:\"<img src=\"./img/tick.png\"> PLMN CSG Select\",\
					in_id_request2_tb:\"<input type=\"button\" id=\"btnSelectReq\" class=\"pbutton\" value=\"Request\" onClick=\"plmnCSGSelect()\">	\",\
					in_id_csg_id_tb:\"CSG ID\",\
					in_id_plmn_id_tb:\"PLMN ID\",\
					in_id_plmn_csg_csgl_tb:\"<img src=\"./img/tick.png\"> PLMN CSG Get CSGL\",\
					in_id_gat_tb:\"<input type=\"button\" id=\"btnGetCSGL\" class=\"pbutton\" value=\"Get\" onClick=\"plmnCSGGetCSGL()\">\",\
					in_id_plmn_csg_acsgl_tb:\"<img src=\"./img/tick.png\"> PLMN CSG Get ACSGL\",\
					in_id_setting_tb:\"<input type=\"button\" id=\"btnSetACSGL\" class=\"pbutton\" value=\"Get\" onClick=\"plmnCSGSetACSGL()\">\",\
					in_id_serch_usim_tb:\"Select USIM\",\
					in_id_index_tb:\"Record Index\",\
					in_id_csg_tb:\"CSG Type IND\",\
					in_id_csg_ind_tb:\"CSG Name IND\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_list_request:\"PLMN CSG List Request Failure!!\",\
					str_alert_fill_blanks:\"Please Fill the Blanks\",\
					str_alert_PLMN_ID:\"Invalid PLMN ID\",\
					str_alert_plmnselect_success:\"PLMN CSG Select Request Success!!\",\
					str_alert_plmnselect_fail:\"PLMN CSG Select Request Failure!!\",\
					str_alert_request_fail:\"PLMN CSG GET CSGL Request Failure!!\",\
					str_alert_invalid_id:\"Invalid PLMN ID\",\
					str_alert_plmn_request_success:\"PLMN CSG Set ACSGL Request Success!!\",\
					str_alert_plmn_request_fail:\"PLMN CSG Set ACSGL Request Failure!!\",\
				},\
			},\
			h_ap_access:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_wifi_setting:\"WiFi Setting\",\
					in_id_access_list1_tb:\"<img src=\"./img/tick.png\">&nbsp; Access List\",\
					in_id_ap_instance_tb:\"AP Instance\",\
					in_id_access_policy_tb:\"Access Policy\",\
					in_id_off_tb:\"Off\",\
					in_id_allow_tb:\"Allow\",\
					in_id_reject_tb:\"Reject\",\
					in_id_mac_Search_tb:\"Connected mac Search\",\
					in_id_access_list2_tb:\"Access List\",\
					in_id_no_tb:\"No.\",\
					in_id_mac_address_tb:\"MAC address (without colon)\",\
				in_id_add_new_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Add new\" onclick=\"addAccessEntry('')\"}>\",\
					in_id_applies_tb:\"<input type=\"button\" id=\"btnwifiaccess\" class=\"pbutton\" value=\"Apply\" onclick=\"wifiSetAccessList()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_enable_ap:\"Cannot find Enabled AP.\n please create AP in AP Setting Page.\",\
					str_alert_setting_change:\"Wifi setting changed successfully\nNeed to restart for the changes to take effect\",\
					str_alert_enable_ap:\"Cannot add more MAC address\",\
					str_alert_mac_length:\"Length of MAC address must be 12!\",\
					str_alert_Wifi_changed:\"Wifi setting changed successfully\",\
					str_alert_AP_restarted:\"Wifi AP is restarted\",\
					str_alert_Remove:\"Remove\",\
				},\
			},\
			h_upload:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_file_upload_tb:\"File Upload\",\
					in_id_file_upload1_tb:\"<img src=\"./img/tick.png\">&nbsp; Upload a file to the system\",\
					in_id_locate_tb:\"Location on the device\",\
					in_id_upload_file_tb:\"File to upload\",\
					in_id_apply_upload_tb:\"<input type=\"button\" class=\"pbutton\" name=\"upload\" id=\"upload\" value=\"Upload\" onclick=\"startUpload()\">\",				\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_chose_file_upload:\"Please select the file to upload\",\
				},				\
			},\
			h_nvlte:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_sys_lte_tb:\"System NV - LTE\",\
					in_id_info_tb:\"Info\",\
					in_id_board_tb:\"Board\",\
					in_id_RF_tb:\"RF Cal\",\
					in_id_ET_tb:\"ET Cal\",\
					in_id_TC_tb:\"TC Cal\",\
					in_id_VENDOR_tb:\"Vender\",\
					in_id_net_info_tb:\"Net Info\",\
					in_id_safety_tb:\"Safety\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},				\
			},\
			h_nvcommon:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_syscommon_tb:\"System Common NV\",\
					in_id_board_set_tb:\"Board Configuration\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},\
			},\
			h_wifiapwps:\
			{\
				innerHTML:\
				{				\
					in_id_wps_set_tb:\"WPS Setting\",\
					in_id_wps_setting_tb:\"<th colspan=\"2\"><img src=\"./img/tick.png\">&nbsp; WPS Setting</th>\",\
					in_id_AP_tb:\"AP Instance\",\
					in_id_ssid_name_tb:\"Network Name (SSID)\",		\
					in_id_certificate_tb:\"Authentication\",\
					in_id_data_tb:\"Encryption\",\
					in_id_network_key:\"Network Key\",\
					in_id_reset_refresh_tb:\"<input type=\"button\" class=\"pbutton\" id=\"btn_reset\" value=\"WPS Reset\" onclick=\"wifiRestartApd()\"><input type=\"button\" class=\"pbutton\" id=\"btn_refresh\" value=\"Refresh\" onclick=\"wifiGetSetting()\"><input type=\"button\" class=\"pbutton\" id=\"btn_apply\" value=\"Apply\" onclick=\"wifiSetSetting()\">\",\
					in_id_registrar1_tb:\"<img src=\"./img/tick.png\">&nbsp; for Internal Registrar</th>\",\
					in_id_connect_tb:\"<input type=\"button\" id=\"btn_registrar_connect\" value=\"WPS Connect\" onclick=\"wps_connect()\">\",\
					in_id_push_button_tb:\"<input type=\"hidden\" id=\"wps_connect_type\" value=\"1\"><input type=\"radio\" name=\"wps_connect_type_radio\" value=\"0\" checked onclick=\"change_wps_method();\">PBC: Push-Button Configuration (PBC)<br/><input type=\"radio\" name=\"wps_connect_type_radio\" value=\"1\" onclick=\"change_wps_method();\">PIN : Setting up connections with PIN - STA PIN <input type=\"text\" class=\"inputtext\" id=\"sta_pin\" style=\"width:80px\">\",\
					in_id_registrar2_tb:\"<img src=\"./img/tick.png\">&nbsp; for Internal Registrar\",\
					in_id_update_tb:\"AP PIN <input type=\"text\" class=\"inputtext\" id=\"ap_pin\" style=\"width:80px\" readonly><input type=\"button\" id=\"btn_ap_pin_renew\" value=\"Renew\" onclick=\"wps_ap_pin_renew()\">\",\
					in_id_state_tb:\"<img src=\"./img/tick.png\">&nbsp; WPS State\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_wifi_wps:\"Wifi WPS setting changed successfully\",\
				str_alert_wps_reset:\"WPS reset complete, reloading the current page\",\
				str_alert_invaild:\"WPS STA PIN is invaild\",\
				},				\
			},	\
			h_wpssetting:\
			{\
				innerHTML:\
				{				\
					in_id_WPS_Setting_tb:\"WPS Setting\",\
					in_id_WPS_Enable_tb:\"<img src=\"./img/tick.png\">&nbsp; WPS Enable\",\
					in_id_WPS_Enable1_tb:\"WPS Enable\",\
					in_id_disable_enable_tb:\"<select class=\"selectbox\" id=\"wps_enable\" style=\"width:150px\" ><option value=\"0\">Disable</option><option value=\"1\">Enable</option></select>\",	\
					in_id_Apply1_tb:\"<input type=\"button\" class=\"pbutton\" id=\"wps_enable_switch\" value=\"Apply\" onclick=\"EnableWPS()\">\",	\
					in_id_wps_setting1_tb:\"<img src=\"./img/tick.png\">&nbsp; WPS Setting\",\
					in_id_WPS_Mode_tb:\"WPS Mode\",\
					in_id_WPS_Pin_tb:\"WPS Pin Mode\",\
					in_id_manual_auto_tb:\"<select class=\"selectbox\" id=\"generate_pin_type\" style=\"width:150px\" onchange=selectPinType()><option value=\"0\">manual</option><option value=\"1\">auto</option><option value=\"2\">client pin</option></select>\",\
					in_id_Pin_tb:\"Pin\",\
					in_id_Generate_PIN_value_tb:\"<input type=\"number\" oninput=\"if(value.length>8) value=value.slice(0,8)\" class=\"inputtext\" id=\"ssid_wps_pin\" style=\"width:150px\"><input type=\"button\" id=\"btn_generate\" value=\"Generate the PIN value\" onclick=\"generate_wps_ap_pin();\">\",\
					in_id_Connect_WPS_tb:\"<input type=\"button\" class=\"pbutton\" id=\"connectWps\" value=\"Connect WPS\" onclick=\"connect_wps()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_pin_length:\"Length of PIN must be 8!\",\
					str_alert_Wifi_changed:\"Wifi setting changed successfully\",\
					str_alert_Applied_WPS:\"Applied WPS PIN successfully! You have to run Wi-Fi Protected Setup within 2 minutes.\",\
					str_alert_WPS_invaild:\"WPS AP PIN is invaild\",\
					str_alert_Start_PBC:\"Start PBC successfully!  You have to run Wi-Fi Protected Setup within 2 minutes.\",\
				},\
			},\
			h_wcdmasettig:\
			{\
				innerHTML:\
				{				\
					in_id_WCDMA1_tb:\"WCDMA Setting\",\
					in_id_WCDMA2_tb:\"<img src=\"./img/tick.png\">&nbsp; WCDMA Enable\",\
					in_id_enable_tb:\"Enable\",\
					in_id_enable_disable_tb:\"<select id=\"wcdma_enable\" class=\"selectbox\" style=\"width:100\"><option value=0>Off</option><option value=1>On</option></select>\",\
					in_id_WCDMA3_tb:\"<img src=\"./img/tick.png\">&nbsp;WCDMA Setting\",\
					in_id_number_tb:\"Number\",\
					in_id_applies_tb:\"<input type=\"button\" class=\"pbutton\" name=\"ButtonApply\" value=\"Apply\" onclick=\"wcdmaSetSetting()\">\",							\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_setting_change:\"Setting has been changed.\nIt Will be applied after next connection\",\
				},				\
			},			\
			h_wifistasetting:\
			{\
				innerHTML:\
				{				\
					in_id_wifi_tb:\"WiFi Setting\",\
					in_id_sta_setting_tb:\"<img src=\"./img/tick.png\">&nbsp; STA Setting\",\
					in_id_enable_tb:\"Enable\",\
					in_id_disable_enable_tb:\"<select class=\"selectbox\" id=\"enable\" style=\"width:150px\"><option value=\"0\">Disable</option><option value=\"1\">Enable</option></select>\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" value=\"Apply\" onclick=\"wifiSetSetting()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_setting_change:\"Wifi setting changed successfully\nNeed to restart for the changes to take effect\",\
				},				\
			},	\
			h_telnet:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_Telnet1_tb:\"Telnet\",\
					in_id_Telnet2_tb:\"<img src=\"./img/tick.png\">&nbsp; Telnet:\",\
					in_id_enable_tb:\"Enable\",\
					in_id_off_on_tb:\"<input type=\"radio\" name=\"enableTelnet\" id=\"enableTelnet\" value=\"0\">OFF&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"enableTelnet\" id=\"enableTelnet\" value=\"1\">ON&nbsp;&nbsp;&nbsp;\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"SetTelnetMode()\">\",		\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_Setting_changed:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"Apply\" onclick=\"SetTelnetMode()\">\",\
				},				\
			},\
		},\
		{\
			h_ban:\
			{\
				title:\"PON Banner\",\
				innerHTML:\
				{\
					in_st:\"系统状态\",\
					in_se:\"高级配置\",\
					in_ma:\"系统管理\",\
					in_us:\"用户管理\"\
				}\
			},\
			h_tr069:\
			{\
				title:\"\",\
				innerHTML:\
				{\
					in_tr069_cfgid:\"TR-069 配置\",\
					in_tr069_Enable:\"启动\",\
					id_disable_tb:\"<input type=\"radio\" name=\"autoexec\" value=\"0\" id=\"Disable\">禁用&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"autoexec\" value=\"1\" id=\"Enable\">开启&nbsp;&nbsp;&nbsp;\",\
					in_Enable:\"开启\",\
					in_url:\"网址:\",\
					in_uname:\"用户名\",\
					in_pwd:\"密码\",\
					in_periodic_inform_enable:\"周期性上报开启\",\
					id_disable_info_tb:\"<input type=\"radio\" name=\"enable\" value=\"0\" checked onClick=\"return periodicSel()\">禁用&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"enable\" value=\"1\" onClick=\"return periodicSel()\">开启&nbsp;&nbsp;&nbsp;\",\
					in_periodic_inform_interval:\"周期性上报间隔\",\
					in_id_interface_tb:\"<img src=\"./img/tick.png\" >&nbsp;连接请求\",\
					in_port:\"端口\"\
				},\
				innerText:\
				{\
					in_id1:\"\",\
					in_id2:\"\"\
				},\
				value:\
				{\
					bt_apply:\"Start UNI loopback test\",\
					in_apply:\"应用\"\
				},\
				js_string:\
				{\
					str_alert_url_empty:\"网址是空\",\
					str_alert_restart_set:\"设置已经被改变.\n需要重启让值生效\",\
					str_alert_uanme_empty:\"用户名是空\",\
					str_alert_pwd_empty:\"密码是空\",\
					str_alert_interval_empty:\"区间是空\",\
					str_alert_interval_invalid:\"区间是无效的!\",\
					str_alert_setting_change:\"设置已经被改变.\n需要重启让值生效\",\
					str_alert_port_empty:\"端口是空!\",\
					str_alert_server_url_empty:\"STUN服务网址是空\",\
					str_alert_server_url_invalid:\"STUN 服务网址长度无效(有效范围长度: 0 ~ 128)\",\
					str_alert_server_port_empty:\"STUN 服务端口是空\",\
					str_alert_nan:\"不是数字\",\
					str_alert_invalid:\"是无效 (有效范围:1~65535)\"\
				}\
			},\
			h_gct:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_sys_info_tb:\"<img src=\"./img/tick.png\">&nbsp; 系统信息\",\
					in_id_device_name:\"设备名称\",\
					in_id_FW_tb:\"固件版本\",\
					in_id_device_HW_tb:\"设备硬件版本\",\
					in_id_FW_date_tb:\"固件日期\"\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},				\
			},\
			h_net:\
			{\
				title:\"网络信息\",\
				innerHTML:\
				{\
					in_id_interface_tb:\"<img src=\"./img/tick.png\">&nbsp;接口\",\
					in_id_name:\"名称\",\
					in_id_netmask:\"子网掩码\",\
					in_id_status:\"状态\",\
					in_id_Gateway_Route_DNS_tb:\"<img src=\"./img/tick.png\">&nbsp;网关,路由, DNS \",\
					in_id_default_Gateway_tb:\"默认网关\",\
					in_id_primary_dns_tb:\"首选 DNS\",\
					in_id_remote_ip_tb:\"远端IP (你的 IP)\",\
					in_id_secondary_dns_tb:\"备用 DNS\",\
					in_id_close_tb: \"关闭\",\
					in_id_open_tb: \"打开\",\
					in_id_dhcp_server:\"DHCP 服务\",\
					in_id_ip_addr_tb:\"IP 地址\",\
					in_id_subnet_mask:\"子网掩码\",\
					in_id_gateway_tb:\"网关\",\
					in_id_dhcp_addr_allocation_tb:\"DHCP分配地址\",\
					in_id_close_nat_tb:\"关闭\",\
					in_id_open_nat_tb:\"打开\",\
					in_id_enable_tb:\"使能\",\
					in_id_close_ipv6_tb:\"关闭\",\
					in_id_open_ipv6_tb:\"打开\",\
					in_id_prefix_len_tb:\"前缀长度\"\
				},\
				value:\
				{\
					ButtonSetBridge:\"应用\",\
					BTN_IPV6:\"应用\",\
				},\
				js_string:\
				{\
					str_alert_url_empty_value:\"空值\",\
					str_alert_nan:\"不是一个数字\",\
					str_alert_not_valid_ip:\"不是一个有效的 IP\",\
					str_alert_setting_change:\"设置已经被改变.\n需要重启让值生效\",\
					str_alert_check_value:\"核对值\",\
					str_alert_prefix_empty:\"前缀长度是空\",\
					str_alert_invalid:\"是无效 (有效范围:1~128)\"\
				}		\
			},\
			h_portforwarding:\
			{\
				title:\"NAT/Router管理\",\
				innerHTML:\
				{				\
					in_id_portforward_setting_tb:\"<img src=\"./img/tick.png\"/>&nbsp; 端口转发设置\",\
					in_id_Rule_name_tb:\"规则名称\",\
					in_id_maximum_length_tb:\"<input type=\"text\" id=\"rule_name\" class=\"inputtext\" onkeypress=\"on_key_press_rulename(this)\" onblur=\"on_key_press_rulename(this)\" style=\"width: 100px\" maxlength=\"20\"/>&nbsp; (最大长度是 20 字符.)\",\
					id_ip_addr_tb:\"IP地址\",\
					in_id_lable_tb:\"设置宿主主机IP地址 (<span id=\"RemoteIPAddress1\"></span>)\",\
					in_id_Protocol_tb:\"协议\",\
					id_extern_port_tb:\"外部端口\",\
					id_inter_port_tb:\"内部端口\",\
					in_id_add_tb:\"<input type=\"button\" class=\"pbutton\" value=\"添加\" onclick=\"port_forwarding_table_add()\">\",\
					in_id_portforward_tb:\"<img src=\"./img/tick.png\"/>&nbsp; 端口转发表\",\
					in_id_No_tb:\"编号\",\
					in_id_rule_name_tb:\"规则名称\",\
					in_id_Ip_addr_tb:\"Ip地址\",\
					in_id_protocol_tb:\"协议\",\
					in_id_extern_port_tbl:\"外部端口\",\
					in_id_inter_port_tbl:\"内部端口\",\
					in_id_delete_tb:\"删除\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" value=\"应用\" id=\"btnport\" onclick=\"SetPortRuleSetting()\">\",\
					in_id_ftp_tb:\"<input type=\"radio\" name=\"nf_ftp\" id=\"nf_ftp\" value=\"1\" >开启&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_ftp\" id=\"nf_ftp\" value=\"0\">禁用&nbsp;&nbsp;&nbsp;\",\
					in_id_nfh323_tb:\"<input type=\"radio\" name=\"nf_h323\" id=\"nf_h323\" value=\"1\" >开启&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_h323\" id=\"nf_h323\" value=\"0\">禁用&nbsp;&nbsp;&nbsp;\",\
					in_id_nf_sip_tb:\"<input type=\"radio\" name=\"nf_sip\" id=\"nf_sip\" value=\"1\" >开启&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_sip\" id=\"nf_sip\" value=\"0\">禁用&nbsp;&nbsp;&nbsp;\",\
					in_id_nf_pptp_tb:\"<input type=\"radio\" name=\"nf_pptp\" id=\"nf_pptp\" value=\"1\" >开启&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_pptp\" id=\"nf_pptp\" value=\"0\">禁用&nbsp;&nbsp;&nbsp;\",\
					in_id_nf_tftp_tb:\"<input type=\"radio\" name=\"nf_tftp\" id=\"nf_tftp\" value=\"1\" >开启&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"nf_tftp\" id=\"nf_tftp\" value=\"0\">禁用&nbsp;&nbsp;&nbsp;\",\
					in_id_epply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"SetALGMode()\">\",\
					in_id_upnp_enable_tb:\"<input type=\"radio\" name=\"upnp_enable\" id=\"upnp_enable\" value=\"1\" >开启&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"upnp_enable\" id=\"upnp_enable\" value=\"0\">禁用&nbsp;&nbsp;&nbsp;\",\
					in_id_appli_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"SetUPNPMode()\">\",\
					in_id_DMZ_tb:\"<img src=\"./img/tick.png\"/>&nbsp; DMZ 设置\",\
					in_id_inter_addr_tb:\"内部IP地址\",\
					in_id_host_addr_tb:\"设置宿主主机IP地址(<span id=\"RemoteIPAddress2\"></span>)\",\
					in_btnDMZsetting:\"应用\",\
					in_btnDMZsetting_tb:\"停止\",\
					in_id_MAC_tb:\"<input type=\"checkbox\" value=\"0\" id=\"mac_checkbox0\" onclick=\"mac_filtering_step(this)\" checked=\"checked\"/><label for=\"mac_checkbox0\"><span>所有允许</span></label>&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" value=\"1\" id=\"mac_checkbox1\" onclick=\"mac_filtering_step(this)\" /><label for=\"mac_checkbox1\"><span>白名单过滤</span></label>&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" value=\"2\" id=\"mac_checkbox2\" onclick=\"mac_filtering_step(this)\" /><label for=\"mac_checkbox2\"><span>黑名单过滤</span></label>&nbsp;&nbsp;<input type=\"button\" class=\"pbutton\" value=\"已上线设备\" style=\"width:160px\" onclick=\"mac_pop()\"/>\",\
					in_id_mac_filter_tb:\"<img src=\"./img/tick.png\"/>&nbsp; MAC过滤\",\
					in_id_mac_addr_tb:\"MAC地址\",\
					in_id_link_time_tb:\"连接时间\",\
					in_id_Add_tb:\"<input type=\"button\" class=\"pbutton\" value=\"增加\" onclick=\"MAC_list_table_add()\"/>\",\
					in_id_MAC_tbl:\"<img src=\"./img/tick.png\"/>&nbsp; MAC列表\",\
					in_id_no_tb:\"编号&nbsp;\",\
					in_id_mac_tb:\"MAC地址\",\
					in_id_del_tb:\"删除\",\
					in_id_eppliy_tb:\"<input type=\"button\" class=\"pbutton\" value=\"应用\" onclick=\"SetMACfilter()\">\",\
					in_cell_innerHTML:\"' value='删除'; onclick='port_forwarding_table_delete()'>\",\
					in_cell_innerHTML_tb:\"' value='删除'; onclick='MAC_list_table_delete()'>\",\
				},\
				 value:\
				{\
				},\
				js_string:\
				{\
					str_alert_portforwarding:\"没有插入规则名称\",\
					str_alert_no_rule_name:\"没有插入规则名称.\",\
					str_alert_special_char:\"不使用特殊字符.\",\
					str_alert_ip_get:\"不能获得 IP 地址.\",\
					str_alert_External_port: \"不能插入外部端口号.\",\
					str_alert_Not_available_inter_port: \"不能插入内部端口号.\",\
					str_alert_Not_get_External_port:\"不能获取外部端口号\",\
					str_alert_Not_get_inter_port:\"不能获取内部端口号\",\
					str_alert_Same_rule_name:\"存在同样的规则名称\",\
					str_alert_MAC_filtering:\"不支持MAC 过滤没有更多项目.\",\
					str_alert_not_available_address:\"无法使用的 MAC 地址.\",\
					str_alert_same_mac_exit:\"存在同样的 Mac 地址.\",\
					str_alert_not_get_mac_addr:\"不能获得MAC地址\",\
					str_alert_iptables_setting_complete:\"Iptables 设置完成\",\
					str_alert_setting_change:\"设置已经改变.\n需要重启让值生效\",\
					str_alert_not_available_ipadress:\"不能获取IP 地址\",\
					str_alert_not_use_this_ip:\"不能使用这个 IP 地址.\",\
					str_alert_DMZ_setting:\"DMZ 设置完成.\",\
					str_alert_add_mac:\"你应该添加 mac 地址.\",\
					str_alert_MAC_filter:\"MAC过滤完成.\",\
				},	\
			},\
			h_ntp:\
			{\
				title:\"NTP 配置\",\
				innerHTML:\
				{\
					in_id_sync_tb:\"<input size=\"24\" name=\"tmptime\" id = \"tmp_time\" value=\"\" type=\"text\" style=\"display:none\"><input size=\"24\" name=\"ntpcurrenttime\" id = \"current_time\" value=\"\" type=\"text\" readonly>&nbsp; &nbsp;<input type=\"button\" value=\"同步到主机\" id=\"manNTPSyncWithHost\" name=\"manNTPSyncWithHost\" onClick=\"syncWithHost()\">\",\
					in_manNTPCurrentTime:\"当前时间:\",\
					in_manNTPTimeZone:\"时区:\",\
					in_manNTPServer:\"NTP 服务\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"manNTPApply\" value=\"应用\" onclick=\"NTPFormCheck()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_setting_change:\"设置已经改变.\n需要重启让值生效\",\
				},		\
			},\
			h_sntp:\
			{\
				title:\"SNTP设置\",\
				innerHTML:\
				{\
					in_hd:\"SNTP设置 \",\
					txt_step:\"正在加载.....\",\
					in_intro:\"为了使用SNTP功能，请选中启用，并设置网络时间服务器。\",\
					in_sntpsta_cur:\"SNTP 当前状态\",\
					in_dis:\"禁用\",\
					in_en:\"启用\",\
					in_primsrvr:\"首选时间服务器:\",\
					in_secsrvr:\"备用时间服务器:\",\
					in_tersrvr:\"备用时间服务器:\",\
					in_timeout:\"超时时间:\",\
					in_pollint:\"更新间隔:\",\
					in_retrcnt:\"重试次数:\",\
					in_tz:\"时区:\",\
					in_dlight_cur:\"夏时制:\"\
				},\
				value:\
				{\
					bt_apply:\"应用\"\
                },\
                option_text:\
				{\
					timezone:[\"(GMT-12:00) 日界线西\",\
						\"(GMT-11:00) 中途岛\",\
						\"(GMT-10:00) 夏威夷\",\
						\"(GMT-09:00) 阿拉斯加\",\
						\"(GMT-08:00) 太平洋时间 (美国，加拿大), 蒂华纳\",\
						\"(GMT-07:00) 亚利桑那; 山地时间 (美国，加拿大)\",\
						\"(GMT-06:00) 中美洲; 中部时间 (美国，加拿大)\",\
						\"(GMT-05:00) 东部时间 (美国，加拿大)\",\
						\"(GMT-04:00) 大西洋时间 (加拿大)\",\
						\"(GMT-03:00) 巴西利亚; 布宜诺斯艾利斯; 格陵兰\",\
						\"(GMT-02:00) 中大西洋\",\
						\"(GMT-01:00) 佛得角群岛\",\
						\"(GMT) 格林威治标准时间：都柏林，里斯本，伦敦；卡萨布兰卡\",\
						\"(GMT+01:00) 阿姆斯特丹，柏林，罗马，斯德哥尔摩，维也纳，巴黎\",\
						\"(GMT+02:00) 雅典，伊斯坦布尔，开罗，哈拉雷，耶路撒冷\",\
						\"(GMT+03:00) 巴格达，科威特，利雅得，莫斯科\",\
						\"(GMT+04:00) 阿曼\",\
						\"(GMT+05:00) 伊斯兰堡，卡拉奇\",\
						\"(GMT+05:30) 钦奈，加尔各答，孟买，新德里\",\
						\"(GMT+06:00) 达卡\",\
						\"(GMT+07:00) 曼谷，汉诺，雅加达\",\
						\"(GMT+08:00) 北京，香港\",\
						\"(GMT+09:00) 东京，首尔\",\
						\"(GMT+10:00) 布里斯本，悉尼\",\
						\"(GMT+11:00) 马加丹，所罗门群岛\",\
						\"(GMT+12:00) 奥克兰, 惠灵顿，斐济\"]\
				},\
				js_string:\
				{\
					str_set_sntp:\"SNTP设置应用\",\
					str_ok:\"成功.\",\
					str_failed:\"失败.\"\
				}\
            },\
            h_user:\
			{\
				title:\"用户\",\
				innerHTML:\
				{		\
					in_id_pwd_setting_tb:\"<img src=\"./img/tick.png\">&nbsp;密码配置:\",\
					in_id_user_tb:\"用户\",\
					in_id_new_pwd_tb:\"新密码:\",\
					in_id_conform_pwd_tb:\"确认密码:\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"ChangePasswd()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_new_passwd_not_empty:\"错误: 新密码不能为空.\",\
					str_alert_pwd_too_long:\"错误! 密码长度太长.\",\
					str_alert_confirmed_pwd_not_empty:\"错误: 确认密码不能为空.\",\
					str_alert_new_diffrent_confirmed_pwd:\"错误: 新密码与确认密码不一致.\",\
					str_alert_setting_change:\"设置已经改变.\n需要重启让值生效\"\
				},\
			},\
			h_diagnostic:\
			{\
				title:\"诊断\",\
				innerHTML:\
				{	\
					in_id_please_wait_tb:\"<img src=\"./img/tick.png\">&nbsp; 请稍后.....\",\
					in_id_ping_diagnostic_tb:\"<img src=\"./img/tick.png\">&nbsp; Ping 诊断:\",\
					in_manPingHost:\"Ping 主机\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"pingApply\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"pingClick()\">\",\
					in_id_Traceout_diagnostic_tb:\"<img src=\"./img/tick.png\">&nbsp; Traceout 诊断:\",\
					in_hosttraceroute:\"Traceout 主机\",\
					in_id_epply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"traceroute\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"tracerouteApply()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_hostip_illegal:\"宿主 ip 非法的!!!\",\
					str_alert_format_error:\"IP格式错误!\",	\
				},				\
			},\
			h_update:\
			{\
				title:\"固件升级\",\
				innerHTML:\
				{\
					in_id_update_image_tb:\"<img src=\"./img/tick.png\">&nbsp; 选固件镜像更新\",\
					in_id_status_tb:\"状态\",\
					in_id_loading_tb:\"<img id=\"img_loading\" src=\"./img/loading.gif\" width=11px height=11px style=\"display:none;\"><input type=text class=\"table_white_desc_text\" id=\"loading\" value=\"请选更新包文件\", size=60 readOnly>\",\
					in_id_update_patch_tb:\"<input type=\"radio\" name=\"formatType\" id=\"format_raw\" value=\"0\" checked >使用原始文件升级(u-boot.bin, uImage, ramdisk.ubifs and tk.gz)<br/><input type=\"radio\" name=\"formatType\" id=\"format_upf\" value=\"1\">使用升级包升级(update_XXX.bin)\",\
					in_id_update_update_tb:\"<input type=\"button\" class=\"pbutton\" id=\"buttonUpload\" value=\"升级\" onclick=\"preFileupload();\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_update_reboot:\"更新成功\n主板将被重启.\",\
					str_alert_Unknown_error:\"未知错误.\",\
					str_alert_chose_update_patch:\"请至少选择一个升级包文件\",\
					str_alert_same_nameselect_again:\"有同名文件, 请再次选择有效文件\",\
					str_alert_Downloading:\"下载... (\",\
					str_alert_update_wait:\"更新成功稍等一下...\",\
					str_alert_update_fail:\"未能更新\",\
					str_alert_loading:\"加载\",\
					str_alert_Check_file:\"核对 F/W 文本 \",\
					str_alert_failed_check_file:\"核对 F/W 文本文件失败\",\
					str_alert_confirm_update_file:\", 请确认更新文件\",\
					str_alert_FW_file:\"F/W 文件 \",\
					str_alert_update_block:\" 更新... 块(\",\
					str_alert_Failed_download:\"未能下载\",\
					str_alert_Filename:\"文件名\",\
				}\
			},\
			h_sysreboot:\
			{\
				title:\"系统重启\",\
				innerHTML:\
				{\
					in_id_reboot_tb:\"<img src=\"./img/tick.png\">&nbsp; 正在重新启动系统\",\
					in_id_waiting_tb:\"请等待.\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_seconds_remaining:\"剩余秒数\",\
				},\
			},\
			h_ssysreboot:\
			{\
				title:\"系统重启\",\
				innerHTML:\
				{\
					in_id_sys_reboot_tb:\"<img src=\"./img/tick.png\">&nbsp;重启系统\",\
					in_id_sys_reboot_take_time_tb:\"系统重启大约花费45秒钟\",\
					in_id_apply_reboot_tb:\<input type=\"button\" class=\"pbutton\" value=\"重启\" onclick=\"rebootstart()\">\"\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},	\
			},\
			h_factoryreset:\
			{\
				title:\"恢复出厂设置\",\
				innerHTML:\
				{				\
					in_id_Factory_Reset_tb:\"<img src=\"./img/tick.png\">&nbsp; 恢复出厂设置\",\
					in_id_reset_all_setting_tb:\"所有设置重置到出厂默认值\",\
					in_id_apply_tb:\"<div id=\"Status\"  ><input type=\"button\"  class=\"pbutton\" id=\"factrst-btn\" value=\"应用\" onclick=\"factoryReset()\"></div>\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_ACK_Factory_Reset:\"出厂重置处理, 网络连接之后你必须重新加载网页..\",\
				},\
			},\
			h_ltestatus:\
			{\
				title:\"LTE 信息\",\
				innerHTML:\
				{				\
					in_id_lte_info_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE 信息\",\
					in_id_FW_tb:\"FW版本\",\
					in_id_sdk_tb:\"SDK版本\",\
					in_id_mac_addr_tb:\"MAC 地址\",\
					in_id_IMEISV_tb:\"IMEISV\",\
					in_id_lte_status_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE 状态\",\
					in_id_uicc_status_tb:\"UICC 状态\",\
					in_id_connect_tb:\"连接\",\
					in_id_pdn_model_tb:\"PDN 类型\",\
					in_id_ipv4_addr_tb:\"IPv4 地址\",\
					in_id_ipv6_addr_tb:\"IPv6 地址\",\
					in_id_plmn_tb:\"PLMN 搜索\",\
					in_id_mcc_tb:\"移动设备国家代码\",\
					in_id_mnc_tb:\"移动设备网络代码\",\
					in_id_plmnselected_tb:\"PLMN ID\",\
					in_id_cell_tb:\"小区 ID\",\
					in_id_cellglobalid_tb:\"小区全局标识符\",\
					in_id_RSSI_tb:\"接收信号强度\",\
					in_id_RSRP_tb:\"参考信号接收功率\",\
					in_id_RSRQ1_tb:\"参考信号接收质量\",\
					in_id_SINR1_tb:\"信噪比\",\
					in_id_band_tb:\"信道\",\
					in_id_EARFCN_tb:\"频点\",\
					in_id_bandwidth_tb:\"频宽\",\
					in_id_txpower_tb:\"发射功率\",\
					in_id_DLThr_tb:\"下行速率\",\
					in_id_servcell_tb:\"连接状态\",\
					in_id_ULThr_tb:\"上行速率\",\
					in_id_roaming_tb:\"漫游状态\",\
					in_id_lte_Statistics_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE 统计\",\
					in_id_RX_pacth_tb:\"接收数据包\",\
					in_id_Tx_pacth_tb:\"发射数据包\",\
					in_id_rx_tb:\"接收字节\",\
					in_id_tx_tb:\"发射字节\",\
					in_id_data_service_status_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE数据业务状态\",\
					in_id_service_status_tb:\"LTE 数据业务状态\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},\
			},\
			h_ltesetting:\
			{\
				title:\"LTE 设置\",\
				innerHTML:\
				{\
					in_id_lte_enable_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE 使能\",\
					in_id_enable_tb:\"使能\",\
					id_close_tb:\"关闭\",\
					id_open_tb:\"打开\",					\
					in_id_apply_tb:\"<input type=\"button\" id=\"btnLteEna\" class=\"pbutton\" name=\"ButtonApply\" value=\"应用\" onclick=\"lteSetEnable()\">\",\
					in_id_lte_connection_tb:\"<img src=\"./img/tick.png\">&nbsp; LTE 连接类型\",\
					in_id_connection_type_tb:\"连接类型\",\
					in_id_epply_tb:\"<input type=\"button\" id=\"btnPdnType\" class=\"pbutton\" name=\"ButtonApply\" value=\"应用\" onclick=\"lteSetPdnType()\">	\",\
					in_id_IMEI_tb:\"<img src=\"./img/tick.png\">&nbsp; IMEI\",\
					in_id_IMEI1_tb:\"IMEI\",\
					in_id_imei_apply_tb:\"<input type=\"button\" id=\"btnIMEI\" class=\"pbutton\" value=\"应用\" onclick=\"lteSetIMEI()\">\",\
					in_id_airplane_tb:\"<img src=\"./img/tick.png\">&nbsp; 飞行模式\",\
					in_id_Mode_tb:\"模式\",\
					in_id_disable_enable_tb:\"<input type=\"radio\" name=\"airplane_mode\" value=\"0\" checked>禁用&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"airplane_mode\" value=\"1\">开启&nbsp;&nbsp;&nbsp;\",\
					in_id_appless_tb:\"<input type=\"button\" id=\"btnAirPlane\" class=\"pbutton\" value=\"应用\" onclick=\"lteSetAirPlane()\">\",	\
					in_id_apn_management_tb:\"<img src=\"./img/tick.png\">&nbsp; APN 配置管理\",\
					in_id_profile_tb:\"配置文件\",\
					in_id_APN_Name_tb:\"APN 名称\",\
					in_id_username_tb:\"用户名\",\
					in_id_pwd_tb:\"密码\",\
					in_id_ltecustomer_tb:\"<input type=\"button\" id=\"lteCustomerNewProfile\" class=\"pbutton\" value=\"新建配置\" onclick=\"lteNewProfile()\">&nbsp;&nbsp;<input type=\"button\" id=\"lteCustomerProfileDelete\" class=\"pbutton\" value=\"删除\" onclick=\"lteProfileDelete()\">&nbsp;&nbsp;	<input type=\"button\" id=\"lteCustomerProfileApply\" class=\"pbutton\" value=\"应用\" onclick=\"lteProfileApply()\">\",\
					in_id_NEW_Profile_tb:\"<img src=\"./img/tick.png\">&nbsp; 新建配置 \",\
					in_id_profile1_tb:\"配置文件\",\
					in_id_apn_name1_tb:\"APN 名称\",\
					in_id_username1_tb:\"用户名\",\
					in_id_pwd1_tb:\"密码\",\
					in_id_apply_cancel_tb:\"<input type=\"button\" id=\"lteNewCustomerProfileApply\" class=\"pbutton\" value=\"应用\" onclick=\"lteNewProfileApply()\">&nbsp;&nbsp;<input type=\"button\" id=\"lteNewCustomerProfileCancel\" class=\"pbutton\" value=\"取消\" onclick=\"lteNewProfileCancel()\">	\",\
					in_id_plmn_search_tb:\"<img src=\"./img/tick.png\">&nbsp; PLMN 搜索类型\",\
					in_id_type1_tb:\"类型\",\
					in_id_PLMN_search3_tb:\"PLMN 搜索\",\
					in_id_PLMN_search_Ext_tb:\"PLMN 外部搜索\",\
					in_id_apples_tb:\"<input type=\"button\" id=\"btnPlmnSearchType\" class=\"pbutton\" value=\"应用\" onclick=\"lteSetPlmnSearchType()\">\",\
					in_id_plmn_search1_tb:\"<img src=\"./img/tick.png\">&nbsp;  PLMN 外部搜索信息\",\
					in_id_search_type_tb:\"搜网方式\",\
					in_id_auto_tb:\"自动\",\
					in_id_manual_tb:\"手动\",\
					in_btnManualPlmnSearching:\"搜索\",\
					in_id_search_mode_tb:\"搜网模式\",\
					in_id_normal_tb:\"正常\",\
					in_id_emergency_tb:\"紧急\",\
					in_id_Roaming_tb:\"漫游\",\
					in_id_enable1_tb:\"使能\",\
					in_id_refuse_tb:\"拒绝\",\
					in_id_Searching_Type_tb:\"搜网类型\",\
					in_id_searching_type1_tb:\"<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"0\">MRU<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"1\">频点<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"2\">信道	<input type=\"radio\" name=\"plmn_ext_searching_type\" value=\"3\">频点范围&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" class=\"pbutton\" id=\"btnPlmnExtSearchingTypeAdd\" value=\"增加\" style=\"width:50px; align:right\" onclick=\"plmn_ext_searching_type_add()\">\",\
					in_btnPlmnExtSearchingTypeAdd:\"增加\",\
					in_id_Type2_tb:\"类型\",\
					in_id_num_of_value_tb:\"参数个数\",\
					in_id_value_tb:\"值\",\
					in_id_NetListTable_tb:\"<img src=\"./img/tick.png\">&nbsp; 网络表单\",\
					in_id_operator_name_tb:\"操作名称\",\
					in_id_operator_code_tb:\"操作码\",\
					in_id_status_tb:\"状态\",\
					in_id_type3_tb:\"类型\",\
					in_id_eppli_tb:\"<input type=\"button\" id=\"btnPlmnExt\" class=\"pbutton\" value=\"应用\" onclick=\"lteSetPlmnExt()\">	\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_IMEI_length:\"IMEI 长度应该是 15.\",\
					str_alert_IMEI_invalid:\"IMEI 是无效. 请再次检查.\",\
					str_alert_PLMNID:\"错误 : 错误 PLMN ID, PLMNID 应该是数字的结合.\",\
					str_alert_PLMNID_length:\"Error : PLMN ID 是无效.\n PLMNID长度是 5 或者 6.\",\
					str_alert_board_reboot:\"\n这板将被重启.\",\
					str_alert_save_reboot_effect:\"保存IMEI完成.\n需要重启让值生效\",\
					str_alert_air_plan_mode:\"设置飞行模式\",\
					str_alert_UE_mode:\"设置UE模式.\",\
					str_alert_sav_PLMN_Searcy:\"保存PLMN Searcy 类型完成\",\
					str_alert_Invalid_value:\"无效的 ECI 值!\",\
					str_alert_Searching_lists:\"搜索类型列表太多.(\",\
					str_alert_max_num_6:\") (最大数 : 6)\",\
					str_alert_Manual_CSG:\"不支持手动选择CSG 模式\",\
					str_alert_fill_blanks:\"请填空.\",\
					str_alert_out_maximum:\"数据长度超过最大值(255).: \",\
					str_alert_plmn_info:\"保存 PLMN 扩展搜索信息完成.\",\
					str_alert_save_APN:\"保存 APN 表格完成\",\
					str_alert_save_jiange_done:\"保存搜索间隔完成\",\
					str_alert_save_IMS_PCAP_reboot_effect:\"保存 IMS PCAP 设置成功.\n需要重启让值生效\",\
					str_alert_num_max_10:\" (最大数 : 10)\",\
					str_alert_invalid_value1:\"已经存在的数值:\",\
					str_alert_num_max_16:\"(最大数 : 16)\",\
					str_alert_num_max_5:\"(最大数 : 5)\",\
					str_alert_searching_type1:\"选择搜索类型\",\
					str_alert_plmn_search_item:\"不支持 plmn 扩展搜索 也不支持标题.\",\
					str_alert_EMM_timer:\"设置 EMM 定时器.\",\
					str_alert_PSM_timer:\"设置 PSM 模式和定时器.\",\
					str_alert_location_service:\"设置定位服务选项.\",\
					str_alert_apntble:\"apntble是空值.\",\
					str_alert_APN_using:\"APN在使用中\",\
					str_alert_APN_table:\"保存APN表项成功\",\
					str_alert_reboot:\"这板将被重启.\",\
					str_alert_profile_null:\"配置文件是空\",\
					str_alert_apn_name:\"apn名称是空\",\
					str_alert_apn_num_full:\"apn数目是空\",\
					str_alert_MRU_count:\"MRU 计数\",\
					str_alert_EARFCN:\"频点\",\
					str_alert_Band:\"信道\",\
					str_alert_EARFCN_Range:\"频点范围\",\
					str_alert_delete:\"' value='删除' style='width:50px;' onclick='plmn_ext_searching_type_delete()'>\",\
					str_alert_Manual_plmn:\"手动plmn搜索完成!\",\
					str_alert_After_setting:\"设置完成后这板将被重启.你想继续么?\",\
					str_alert_connection_lost:\"设置完成后连接将丢失.你想继续么?\",\
				}\
			},\
			h_sim_pin:\
			{\
				title:\"LTE SIM PIN\",\
				innerHTML:\
				{				\
					in_id_pin_info_tb:\"<img src=\"./img/tick.png\">&nbsp;  PIN 信息\",\
					in_id_pin_sta_tb:\"PIN 状态\",\
					in_id_retries_pin_tb:\"重试 PIN\",\
					in_id_retries_puk_tb:\"重试 PUK\",\
					in_id_refresh_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_REFRESH\" value=\"刷新\" onclick=\"getPinStatus()\">\",\
					in_id_pin_management_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN 管理\",\
					in_id_pin_code_tb:\"PIN码\",\
					in_id_enablePin_disable_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_VERIFY\" value=\"证实\" onclick=\"verifyPin()\"><input type=\"button\" class=\"pbutton\" id=\"BTN_ENABLE\" value=\"使能\" onclick=\"enablePin()\"><input type=\"button\" class=\"pbutton\" id=\"BTN_DISABLE\" value=\"禁止\" onclick=\"disablePin()\">\",\
					in_id_pin_change_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN 更改\",\
					in_id_pin_code1_tb:\"PIN码\",\
					in_id_new_pin_code_tb:\"新PIN码\",\
					in_id_confirm_pin_code_tb:\"确认新PIN码\",\
					in_id_changepin_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_CHANGE\" value=\"更改\" onclick=\"changePin()\">\",\
					in_id_pin_unblock_tb:\"<img src=\"./img/tick.png\">&nbsp; PIN 开启\",\
					in_id_puk_code_tb:\"PUK 码\",\
					in_id_new_pin_code1_tb:\"新PIN码\",\
					in_id_unlock1_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_UNBLOCK\" value=\"开启\" onclick=\"unblockPin()\">\",\
					in_id_sim_lock_tb:\"<img src=\"./img/tick.png\">&nbsp; SIM 锁\",\
					in_id_sim_lock1_tb:\"SIM 锁\",\
					in_id_unlock_tb:\"解锁\",\
					in_id_lock_tb:\"锁\",\
					in_id_eppli_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_SIM_LOCK\" value=\"应用\" onclick=\"lockSIM()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_verify_fail:\"证实失败\",\
					str_alert_Verify_OK:\"证实成功\",\
					str_alert_enable_fail:\"使能失败\",\
					str_alert_enable_ok:\"使能成功\",\
					str_alert_disable_fail:\"禁止失败\",\
					str_alert_disable_ok:\"禁止成功\",\
					str_alert_incorrect_new_pin:\"错误的新PIN\",\
					str_alert_change_fail:\"更新失败\",\
					str_alert_change_ok:\"更新成功\",\
					str_alert_unblock_fail:\"开启失败\",\
					str_alert_unblock_ok:\"开启成功\",\
					str_alert_lock_unlock:\"启用/关闭 SIM 成功!\",\
					str_alert_reboot:\"\n这板将被重启.\",\
					str_alert_locked_status:\"SIM 是被锁的状态!\",\
					str_alert_unlocked_status:\"SIM 是解锁的状态!\",\
				},\
			},\
			h_ltesms:\
			{\
				title:\"SMS 发送/接收\",\
				innerHTML:\
				{\
					in_id_title_tb:\"SMS 发送/接收\",\
					in_id_conf_tb:\"<img src=\"./img/tick.png\">&nbsp; 配置\",\
					in_id_sms_mo_format_tb:\"SMS MO 格式\",\
					in_id_Storage_tb:\"存储\",\
					in_id_ims_test_tb:\"IMS测试模式\",\
					in_id_disable_tb:\"禁用\",\
					in_id_enable_tb:\"启用\",\
					in_id_disable1_tb:\"禁用\",\
					in_id_enable1_tb:\"启用\",\
					in_id_eppli_tb:\"<input type=\"button\" id=\"btnConfig\" class=\"pbutton\" name=\"ConfigApply\" value=\"应用\" onclick=\"setSMSConfig()\">\",\
					in_id_sms_status_tb:\"<img src=\"./img/tick.png\">&nbsp; SMS 状态\",\
					in_id_nv_info_tb:\"NV 信息\",\
					in_id_uicc_info_tb:\"UICC 信息\",\
					in_id_SCA_tb:\"短信中心号码\",\
					in_id_apply_tb:\"<input type=\"button\" id=\"btnSaveSCA\" class=\"pbutton\" value=\"应用\" onclick=\"setSCA()\">\",\
					in_id_epply_tb:\"<input type=\"button\" id=\"btnSavePSISMSC\" class=\"pbutton\" value=\"应用\" onclick=\"setPSISMSC()\">\",\
					in_id_user_psismsc_tb:\"用户 PSISMSC\",\
					in_id_eppli1_tb:\"<input type=\"button\" id=\"btnSaveUserPSISMSC\" class=\"pbutton\" value=\"应用\" onclick=\"setUserPSISMSC()\">\",\
					in_id_sms_info_tb:\"<img src=\"./img/tick.png\">&nbsp; SMS信息\",\
					in_id_recive_info_tb:\"接收信息\",\
					in_id_format_tb:\"格式\",\
					in_id_document_tb:\"文本 3GPP2\",\
					in_id_document1_tb:\"文本 3GPP\",\
					in_id_storage_tb:\"存储\",\
					in_id_Filter_tb:\"过滤器\",\
					in_id_all_tb:\"所有\",\
					in_id_unread_tb:\"未读\",\
					in_id_read_tb:\"已读\",\
					in_id_unsent_tb:\"未发出\",\
					in_id_sent_tb:\"已发出\",\
					in_id_refresh_tb:\"<input type=\"button\" id=\"btnRefreshSMS\" class=\"pbutton\" style=\"width:120px\" value=\"刷新\" onclick=\"RefreshReceiveSMS()\">\",\
					in_id_index_tb:\"索引\",\
					in_id_Priority_tb:\"优先级\",\
					in_id_storage1_tb:\"存储\",\
					in_id_direction_tb:\"来源/目的地\",\
					in_id_type_tb:\"类型\",\
					in_id_time_tb:\"时间\",\
					in_id_info_tb:\"信息\",\
					in_id_delete_msg_tb:\"删除消息\",\
					in_id_index1_tb:\"索引\",\
					in_id_read1_tb:\"接收\",\
					in_id_sent1_tb:\"发送\",\
					in_id_read_sent_unsent_tb:\"未发出\",\
					in_id_all1_tb:\"全部\",\
					in_id_delete_tb:\"<input type=\"button\" id=\"btnDeleteSMS\" class=\"pbutton\" style=\"width:120px\" value=\"删除\" onclick=\"DeleteSMS()\">\",\
					in_id_sent_msg_tb:\"发送消息\",\
					in_id_format1_tb:\"格式\",\
					in_id_first_tb:\"优先\",\
					in_id_normal_tb:\"普通\",\
					in_id_Interactive_tb:\"交互\",\
					in_id_urgent_tb:\"紧急的\",\
					in_id_emergency_tb:\"紧急情况\",\
					in_id_privacy_tb:\"隐私\",\
					in_id_no_Restricted_tb:\"不受限制的\",\
					in_id_restricted_tb:\"受限制的\",\
					in_id_Confidential_tb:\"机密的\",\
					in_id_secret_tb:\"秘密\",\
					in_id_Alert_tb:\"警惕\",\
					in_id_default_tb:\"默认\",\
					in_id_low_tb:\"低的\",\
					in_id_medium_tb:\"中等\",\
					in_id_high_tb:\"高的\",\
					in_id_char_set_tb:\"字符集设置(GSM/ASCII)\",\
					in_id_reply_tb:\"回复\",\
					in_sms_reply_user:\"用户\",\
					in_sms_reply_delivery:\"交付\",\
					in_sms_reply_read:\"阅读\",\
					in_sms_reply_report:\"报告\",\
					in_id_info1_tb:\"信息\",\
					in_id_direction2_tb:\"目的地\",\
					in_id_format1_tb:\"格式\",\
					in_id_storage2_tb:\"存储位置\",\
					in_id_senta_tb:\"<input type=\"button\" id=\"btnSendSMS\" class=\"pbutton\" style=\"width:120px\" value=\"发送\" onclick=\"SendSMS()\">\",\
					in_loadingDiv:\"请等待..\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_Retry_finished:\"\n重试完成\n\",\
				str_alert_ACK_Success:\"短信发送确认成功\",\
				str_alert_ACK_NO_action:\"短信发送确认无操作\",\
				str_alert_sca_conf:\"保存 SCA 配置.\",\
				str_alert_psismsc_conf:\"保存 PSISMSC 配置.\",\
				str_alert_save_psismsc_conf:\"保存用户 PSISMSC 配置.\",\
				str_alert_save_sms_reboot:\"保存 SMS 配置.\n这个板将重新启动.\",\
				str_alert_get_sms_conf:\"获取SMS IMS配置\",\
				str_alert_sms_sending:\"\n重试短信发送.\n  20 秒之后\n\",\
				str_alert_result:\"\n失败短信\n结果 :\",\
				str_alert_sms_send_fail:\"\n短信发送失败.\n\",\
				str_alert_sms_sending_20:\"\n重试短信发送.\n20秒之后\n\",\
				str_alert_sms_fail:\"\n短信发送失败.\n\",\
				str_alert_sms_cause:\"\n短信结果原由 :\",\
				str_alert_sms_fail_no_reply:\"\n短信发送失败.\n没有回复.\",\
				str_alert_sms_send_ok:\"短信发送确认成功\",\
				str_alert_SMS_content:\"选择短信内容\",\
				str_alert_delete_reload_list:\" 短信已经删除, 重新导入表单中\",	\
				str_alert_sms_refresh_ok:\"短信刷新成功！\",\
				},\
			},\
			h_wifistatus:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_title_tb:\"WiFi 信息\",\
					in_id_wifi_status_tb:\"<img src=\"./img/tick.png\">&nbsp; WiFi状态\",\
					in_id_ap_instance_tb:\"AP实例\",\
					in_id_network_name_tb:\"网络名称(SSID)\",\
					in_id_network_mode_tb:\"网络模式\",\
					in_id_rx_packets_tb:\"接收数据包\",\
					in_id_tx_packets_tb:\"发射数据包\",\
					in_id_RX_Byte_tb:\"接收字节\",\
					in_tx_byte_tb:\"发射字节\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_cannot_find_enabled_ap_setting_page:\"不能发现使能 AP.\n 请创建 AP 在 AP 设置页面.\",\
				},\
			},\
			h_wificommon:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_wifi_settig_tb:\"WiFi 设置\",\
					in_id_common_setting_tb:\"<img src=\"./img/tick.png\">&nbsp; 通用设置\",\
					in_id_Freqency_channel_tb:\"信道\",\
					in_id_auto_tb:\"自动\",\
					in_id_tx_power_tb:\"发射功率\",\
					in_id_beacon_interval_tb:\"信标间隔\",\
					in_id_preamble_tb:\"前导码\",\
					in_id_long_tb:\"长的\",\
					in_id_short_tb:\"短的\",\
					in_id_apply_tb:\"<input type=\"button\" id=\"btnwificommon\" class=\"pbutton\" value=\"应用\" onclick=\"wifiSetCommon()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_wifi_setting_change_ok:\"Wifi 设置改变成功\n\",\
				},\
			},\
			h_wifisetting:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_wifi_setting_tb:\"WiFi 设置\",\
					in_id_AP_Enable_tb:\"<img src=\"./img/tick.png\">&nbsp; AP 开启:\",\
					in_id_enable_tb:\"开启\",\
					in_id_disable_enable_tb:\"<input type=\"radio\" name=\"autoexec\" value=\"0\" >禁用&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"autoexec\" value=\"1\">使能&nbsp;&nbsp;&nbsp;\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"ap_enable_switch\" value=\"应用\" onclick=\"EnableAP()\">\",\
					in_id_ap_setting1_tb:\"<img src=\"./img/tick.png\">&nbsp; AP 设置\",\
					in_id_start_wlan_tb:\"启动 wlan\",\
					in_id_wps_enable_tb:\"WPS 开启\",\
					in_id_disable1_tb:\"禁止\",\
					in_id_enable1_tb:\"开启\",\
					in_id_Network_name_tb:\"SSID名称\",\
					in_id_Network_mode_tb:\"协议\",\
					in_id_Frequency_Band_tb:\"频段范围\",\
					in_id_Max_No_station_tb:\"支持的最大连接数\",\
					in_id_Hidden_ssid_tb:\"隐藏 SSID\",\
					in_id_Off_tb:\"关闭\",\
					in_id_On_tb:\"打开\",\
					in_id_authentication_tb:\"认证方式\",\
					in_id_encryption_tb:\"加密方式\",\
					in_id_network_key_tb:\"网络密钥\",\
					in_id_key_Type_tb:\"密钥类型\",\
					in_id_index_to_use_tb:\"使用索引\",\
					in_id_input_key_tb:\"请输入本次密钥\",\
					in_id_appli_tb:\"<input type=\"button\" id=\"btnwifiSet\" class=\"pbutton\" value=\"应用\" onclick=\"wifiSetSetting()\">\",\
					in_id_ap_list_tb:\"<img src=\"./img/tick.png\">&nbsp; AP 列表\",\
					in_id_instance_tb:\"实例\",\
					in_id_RF_Mode_tb:\"RF模式\",\
					in_id_encrytion_tb:\"功能\",\
					in_id_add_ap_tb:\"<input type=\"button\" id=\"btnwifiAdd\" class=\"pbutton\" value=\"增加 AP\" onclick=\"addAPToList()\">\",\
					in_id_eppli_tb:\"<input type=\"button\" id=\"btnAPListApply\" class=\"pbutton\" value=\"应用\" onclick=\"wifiRestartApd()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_instance_select_11ac:\"只有一个实例能选择 11ac. 请再一次检查.\",\
				str_alert_add_new_ap_instance:\"请添加到新 AP 实例.\",\
				str_alert_not_matching_index:\"不匹配的密钥索引\n 请输入密钥\",\
				str_alert_error:\"错误\",\
				str_alert_change1_success:\"Wifi 设置改变成功\",\
				str_alert_change_success:\"Wifi 设置改变成功\n需要重启让值生效\",\
				str_alert_restart:\"Wifi AP 被重启\",\
				str_alert_cannot_support_ap_instance:\"不能加入新的 AP 实例, 因为还没有 3 AP 实例.\",\
				str_alert_cannot_support_multiple:\"不能加入新的 AP 实例, 因为还没有支持 multiple AP 实例.\",\
				str_alert_ap_added_reloading:\"AP 删除, 重新导入清单\",\
				str_alert_startPBC_seccess:\"成功启动PBC! 你不得不安装Wi-Fi保护在两分钟内 .\",\
				str_alert_pin_is_null:\"PIN 是空\",\
				str_alert_apply_wpspin_successfully:\"应用 WPS PIN 成功! 你不得不安装Wi-Fi保护在两分钟内 .\",\
				str_alert_wps_ap_invaild:\"WPS AP PIN 是有效的\",\
				str_alert_wifi_setting_change:\"Wifi 设置改变成功\",\
				str_alert_Remove:\"移除\",\
				},\
			},\
			h_syslog:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_sys_logtitle_tb:\"系统日志\",\
					in_id_sys_log:\"<img src=\"./img/tick.png\">&nbsp; 系统日志\",\
					in_id_default_Manual_tb:\"默认/手动\",\
					in_id_default_tb:\"默认\",\
					in_id_Manual_tb:\"手动\",\
					in_id_log_mask_tb:\"日志Mask\",\
					in_id_tag_tb:\"标签\",\
					in_id_Description_tb:\"描述\",\
					in_id_use_tb:\"使用\",\
					in_id_level_tb:\"等级\",\
					in_id_add_tag_tb:\"添加标题\",\
					in_id_add_tb:\"<input type=\"button\" class=\"pbutton\" value=\"增加\" onclick=\"onClickAddLogMask();\">\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" value=\"应用\" onclick=\"onClickApplyLogMask()\">\",\
					in_id_sys_log_save_tb:\"<img src=\"./img/tick.png\">&nbsp; 保存系统日志\",\
					in_id_disable_enable_tb:\"<input type=\"radio\" name=\"logsave\" id=\"nand\" value=\"0\" checked >禁用&nbsp;<input type=\"radio\" name=\"logsave\" id=\"dram\" value=\"1\">使能&nbsp;\",\
					in_id_appli_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BtnSetLogSave\" value=\"应用\" onclick=\"SetLoggingType()\">\",\
					in_id_add_dm_tb:\"<img src=\"./img/tick.png\">&nbsp; 增加DM指令到启动脚本\",\
					in_id_enable_log_tb:\"使能日志\",\
					in_id_enable_desable_tb:\"<input type=\"radio\" name=\"q_log\" id=\"q_log_disable\" value=\"0\">禁止<input type=\"radio\" name=\"q_log\" id=\"q_log_enable\" value=\"1\">使能\",\
					in_id_lte_log_locate_tb:\"LTE日志位置\",\
					in_armlog_uart:\"<input type=\"radio\" name=\"arm1log\" id=\"armlog_uart\" value=\"1\">串口<input type=\"radio\" name=\"arm1log\" id=\"arm1log_lted_cli\" value=\"2\">缓冲区<input type=\"radio\" name=\"arm1log\" id=\"arm1log_file\" value=\"3\">文件\",\
					in_id_init_dm_tb:\"初始化DM指令\",\
					in_id_applie_tb:\"<input type=\"button\" class=\"pbutton\" value=\"应用\" onclick=\"setScript()\">\",\
					in_id_download_log_tb:\"<img src=\"./img/tick.png\">&nbsp; 下载日志文件\",\
					in_id_file_name_tb:\"文件名\",\
					in_id_reboot_tb:\"<input type=\"button\" class=\"pbutton\" title=\"Download\" value=\"重启\" onclick=\"resetLogFile('all')\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_setting_change_reboot:\"设置已经改变.\n需要重启保存系统调试日志\",\
				str_alert_tag_name_null:\"标签名是空!\",\
				str_alert_tag_name_exist:\"输入tag 名称已经存在!\",\
				str_alert_save_log_done_reboot:\"保存日志屏蔽完成.\n需要重启让值生效\",\
				str_alert_save_DM_reboot:\"保存 DM 指令成功.\n需要重启让值生效\n\",\
				str_alert_down_load:\"<input type='button' class='pbutton' title='Download' value='下载'>\",\
				str_alert_delete:\"<input type='button' class='pbutton' title='Delete' value='删除' onClick='resetLogFile(\"\",\
				},\
			},\
			h_left:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_system1:\"系统\",\
					in_id_system21:\"状态\",\
					in_id_system22:\"网络\",\
					in_id_system222:\"网络\",\
					in_id_system23:\"连接管理\",\
					in_id_portforwarding:\"NAT/Router 管理\",\
					in_id_tr069:\"TR069\",\
					in_id_ntp:\"NTP\",\
					in_id_user:\"用户\",\
					in_id_diagnostic:\"诊断\",\
					in_id_system24:\"固件升级\",\
					in_id_system25:\"恢复出厂设置\",\
					in_id_system27:\"重启\",\
					in_id_system28:\"系统语言\",\
					in_id_lte1:\"LTE\",\
					in_id_lte21:\"状态\",\
					in_id_ltesetting1:\"设置\",\
					in_id_ltesetting2:\"设置\",\
					in_id_lte24:\"SIM PIN\",\
					in_id_lte25:\"短信\",\
					in_id_volte:\"高清语音\",\
					in_id_lte26:\"OTA-DM\",\
					in_id_lteplmncsg:\"PLMN CSG\",\
					in_id_wifiap1:\"WiFi\",\
					in_id_wifiap21:\"AP 状态\",\
					in_id_wifiap22:\"AP 通用\",\
					in_id_wifiap23:\"AP 设置\",\
					in_id_wifiap24:\"AP 访问控制\",\
					in_id_wifiap25:\"AP WPS 设置\",\
					in_id_wifista26:\"STA 设置\",\
					in_id_engineer1:\"工程\",\
					in_id_engineer24:\"文件上传\",\
					in_id_engwimaxnv:\"NV-Wimax\",\
					in_id_engltenv:\"NV-LTE\",\
					in_id_engcommonnv:\"NV-Common\",\
					in_id_englog:\"日志\",\
					in_id_Expand:\"扩展\",\
					in_id_Collapse:\"折叠\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_tag_name1_null:\"提示名称为空!\"\
				},\
			},\
			h_syslanguage:\
			{\
				title:\"PON Banner\",\
				innerHTML:\
				{\
					in_id_language_tb:\"<img src=\"./img/tick.png\">&nbsp; 语言设定:\",\
					in_id_language_transformation_tb:\"语言转换\",\
					in_id_epplie_tb:\"<input type=\"button\" class=\"pbutton\" id=\"language_enable_switch\" value=\"应用\" onclick=\"Enablelanguage()\">\",\
					in_id_ch_en_tb:\"<input type=\"radio\" name=\"autoexec\" value=\"0\" >英文&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"autoexec\" value=\"1\">中文&nbsp;&nbsp;&nbsp;\",\
					in_id_enable_tb:\"启用\"\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_seting_changed:\"设置已经改变.\n\",\
				},\
		},			\
			h_mac_pop:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_connect_mac_tb:\"<img src=\"./img/tick.png\">&nbsp; 连接的MAC列表\",\
					in_id_no_tb:\"编号&nbsp;\",\
					in_id_ipaddr_tb:\"Ip 地址\",\
					in_id_mac_addr_tb:\"Mac 地址\",\
					in_id_appli_cancel_tb:\"<input type=\"button\" class=\"pbutton\" name=\"Apply\" value=\"应用\" onclick=\"returnParsed()\"><input type=\"button\" class=\"pbutton\" name=\"Cancel\" value=\"取消\" onclick=\"window.close()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_check_any_one:\"你应该打勾任何一个.\",\
						str_alert_mac_addr_done:\"Mac 地址设置完成.\n请点击添加按钮.\",\
				},\
			},\
			h_home:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_Reference_tb:\"CPE 参考网页\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},\
			},\
			h_cm:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_cm_tb:\"连接管理\",\
					in_id_RF_tb:\"<img src=\"./img/tick.png\">&nbsp; RF 连接状态和设置\",\
					in_id_up_down_tb:\"向上/向下\",\
					in_id_priority_tb:\"优先级\",\
					in_id_name_tb:\"名称\",\
					in_id_enable_tb:\"开启\",\
					in_id_status_tb:\"状态\",\
					in_id_appplies_tb:\"<input type=\"button\" class=\"pbutton\" id=\"btnPriority\" name=\"ButtonApply\" value=\"应用\" onclick=\"setPriority()\">	\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_no_change_priority:\"不需要改变优先级\",\
					str_alert_top_priority:\"早已最高优先级\",\
					str_alert_lowest_priority:\"早已是最低优先级\",\
					str_alert_up:\"向上\",\
					str_alert_down:\"向下\",\
					str_alert_on:\"打开\",\
					str_alert_off:\"关闭\",\
					str_alert_setting_change_reboot1:\"设置已经改变\n需要重启让值生效\",\
				},\
			},\
			h_VoLTE:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_Vo_Set_tb:\"高清语音设置\",\
					in_id_setting_tb:\"<img src=\"./img/tick.png\">&nbsp; 设置\",\
					in_id_enable_tb:\"使能\",\
					in_id_off_tb:\"关闭\",\
					in_id_on_tb:\"打开\",\
					in_id_session_timer_tb:\"会话时间IMS\",\
					in_id_sec_tb:\"<input type=\"text\" class=\"inputtext\" id=\"session_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_sec1_tb:\"<input type=\"text\" class=\"inputtext\" id=\"min_se_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_on_off1_tb:\"	<input type=\"radio\" name=\"amrwb_mode\" value=\"0\">关闭&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"amrwb_mode\" value=\"1\">打开\",\
					in_id_on_off2_tb:\"<input type=\"radio\" name=\"scr_amr_mode\" value=\"0\">关闭&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"scr_amr_mode\" value=\"1\">打开\",\
					in_id_on_off3_tb:\"<input type=\"radio\" name=\"scr_amrwb_mode\" value=\"0\">关闭&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"scr_amrwb_mode\" value=\"1\">打开\",\
					in_id_ring_tb:\"<span id=\"tb_0700\">响铃Timer IMS</span>\",\
					in_id_sec2_tb:\"<input type=\"text\" class=\"inputtext\" id=\"ringing_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_ringback_tb:\"回铃 Timer IMS\",\
					in_id_sec3_tb:\"<input type=\"text\" class=\"inputtext\" id=\"ringback_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_RTP_RTCP_tb:\"RTP RTCP 不工作 Timer IMS\",\
					in_id_sec4_tb:\"<input type=\"text\" class=\"inputtext\" id=\"rtp_rtcp_inactivity_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_UDP_tb:\"<span id=\"tb_1000\">UDP保持激活</span>\",\
					in_id_sec5_tb:\"<input type=\"text\" class=\"inputtext\" id=\"udp_keep_alive\" style=\"width:150\">&nbsp;秒\",\
					in_id_T1_Timer_tb:\"T1 定时器 IMS\",\
					in_id_sec6_tb:\"<input type=\"text\" class=\"inputtext\" id=\"t1_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_T2_Timer_tb:\"T2 定时器 IMS\",\
					in_id_sec7_tb:\"<input type=\"text\" class=\"inputtext\" id=\"t2_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_TF_IMS_tb:\"TF Timer IMS\",\
					in_id_sec8_tb:\"<input type=\"text\" class=\"inputtext\" id=\"tf_timer_ims\" style=\"width:150\">&nbsp;秒\",\
					in_id_tty_tb:\"<span id=\"tb_1400\">TTY模式</span>\",\
					in_id_CHO_VCO_tb:\"<input type=\"radio\" name=\"TTY_mode\" value=\"0\" checked>关闭&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"TTY_mode\" value=\"1\" >HCO&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"TTY_mode\" value=\"2\">VCO&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"TTY_mode\" value=\"3\">全部\",\
					in_id_pcmu_tb:\"<span id=\"tb_1500\">Pcmu使能</span>\",\
					in_id_enable_disable_tb:\"<input type=\"radio\" name=\"pcmuenable_mode\" value=\"0\" checked>禁用&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"pcmuenable_mode\" value=\"1\" >启动\",\
					in_id_confserv_tb:\"<span id=\"tb_1600\">Confserv链接</span>\",	\
					in_id_all_reboot_tb:\"<input type=\"button\" id=\"applybutton\" class=\"pbutton\" value=\"全部应用&重启\" onclick=\"set_volte_setting()\" style=\"width:600\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_Session_Timer:\" 会话计时器IMS范围 : 90 ~ 7200\",\
					str_alert_Min_Se:\"最小 Se IMS 范围 : 90 ~ 3600\",\
					str_alert_RTP_RTCP:\"RTP RTCP 非活动计时器 IMS 范围 : 10 ~300\",\
					str_alert_board_reboot:\"设置之后这板将会重启，你想继续么？\",\
				},\
			},\
			h_otadm:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_defer_download_dialog:\"<p>什么时候你想要下载这更新?</p>\",\
					in_defer_update_dialog:\"<p>什么时候你想要更新这更新?</p>\",\
					in_download_dialog_mandatory:\"<p>你想要下载固件包?</p>\",\
					in_download_dialog_optional:\"<p>你想要下载固件包?</p>\",\
					in_update_dialog_optional:\"<p>你想要更新固件包?</p>\",\
					in_update_success_dialog:\"<p>重新启动你的 IMG03 为了来完整的安装.<br>为了给重启你的 IMG03 将花费大约 3 分钟.</p>\",\
					in_loadingDiv:\"请稍后..\",\
					in_id_lte_fota_test_tb:\"LTE FOTA 测试页\",	\
					in_id_info_tb:\"<img src=\"./img/tick.png\">&nbsp; 信息\",	\
					in_id_current_status_tb:\"当前状态\",	\
					in_id_operation_tb:\"<img src=\"./img/tick.png\">&nbsp; 操作\",\
					in_id_check_again_tb:\"核对新的 S/W 包\",\
					in_id_check_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_CHECK_NEW_SW\" value=\"核对\" onclick=\"runOtaDmCheckForNewSU()\" style=\"width:150px\">\",\
					in_id_server_tb:\"OTA DM 服务器设置 <br/>(只针对 IOT)\",\
					in_id_server_ip_tb:\"服务器地址 <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SERVER_ADDR\" style=\"width:200px\">\",\
					in_id_set_get1_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_SERVER_ADDR\" value=\"获取\" onclick=\"getOtaDmInfo(0)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_SERVER_ADDR\" value=\"设置\" onclick=\"setOtaDmInfo(0)\" style=\"width:70px\">\",\
					in_id_server_port_tb:\"服务器端口 <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SERVER_PORT\" style=\"width:200px\">\",	\
					in_id_get_set2_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_SERVER_PORT\" value=\"获取\" onclick=\"getOtaDmInfo(1)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_SERVER_PORT\" value=\"设置\" onclick=\"setOtaDmInfo(1)\" style=\"width:70px\">\",\
					in_server_ip_type_tb:\"服务器地址类型 <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SERVER_ADDR_TYPE\" style=\"width:200px\">\",\
					in_id_get_set3_tb:\"	<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_SERVER_ADDR_TYPE\" value=\"获取\" onclick=\"getOtaDmInfo(2)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_SERVER_ADDR_TYPE\" value=\"设置\" onclick=\"setOtaDmInfo(2)\" style=\"width:70px\">\",\
					in_id_sw_tb:\"SW 版本 <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_SW_VERSION\" style=\"width:200px\">\",\
					in_id_get_set4_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_SW_VERSION\" value=\"获取\" onclick=\"getOtaDmInfo(3)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_SW_VERSION\" value=\"设置\" onclick=\"setOtaDmInfo(3)\" style=\"width:70px\">\",\
					in_id_FW_version_tb:\"FW 版本 <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_FW_VERSION\" style=\"width:200px\">\",\
					in_id_get_set5_tb:\"	<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_FW_VERSION\" value=\"获取\" onclick=\"getOtaDmInfo(4)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_FW_VERSION\" value=\"设置\" onclick=\"setOtaDmInfo(4)\" style=\"width:70px\">\",\
					in_id_HW_version_tb:\"HW 版本 <br/><input type=\"text\" class=\"inputtext\" id=\"OTA_DM_HW_VERSION\" style=\"width:200px\">\",\
					in_id_get_set_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_GET_OTA_DM_HW_VERSION\" value=\"获取\" onclick=\"getOtaDmInfo(5)\" style=\"width:70px\"><input type=\"button\" class=\"pbutton\" id=\"BTN_SET_OTA_DM_HW_VERSION\" value=\"设置\" onclick=\"setOtaDmInfo(5)\" style=\"width:70px\">\",\
					in_id_non_interaction_mode_tb:\"非-交互模式\",	\
					in_id_non_usb_mode_tb:\"<div id=\"TXT_NONINTERACTION_MODE\" >非-USB模式</div>\",	\
					in_id_on_off_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_INTERACTION_MODE\" value=\"开关\" onclick=\"runNoninteracionMode()\" style=\"width:150px\">\",\
					in_id_OTA_NV_tb:\"OTA NV 重置\",\
					in_id_reset_tb:\"<input type=\"button\" class=\"pbutton\" id=\"BTN_OTA_NV_RESET\" value=\"重置\" onclick=\"runOtaNvReset()\" style=\"width:150px\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_SW_available:\"新的 SW 更新是无效的\",\
					str_alert_OTA_DM:\"不能获得 OTA-DM 状态\",\
					str_alert_OTA_session:\"OTA 会话已经在运行中\n请稍后再试\",\
					str_alert_storage_space:\"它将为 OTA-DM/FOTA 清理所有的存储空间.\n它应该在OOB状态下只执行一次.\nIMG03 将被关闭并且开启.\",\
					str_alert_send_success:\"成功发送结果\",\
					str_alert_send_fail:\"发送结果失败，请稍后重试\",\
					str_alert_get:\"获得\",\
					str_alert_info:\"信息成功\",\
					str_alert_fail_get:\"不能获得\",\
					str_alert_info1:\"信息\",\
					str_alert_success:\"成功\",\
					str_alert_fail_set:\"不能设置\",\
					str_alert_info2:\"信息\",\
				},\
			},\
			h_plmncsg:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_PLMN_CSG1_tb:\"CPE PLMN CSG\",\
					in_id_PLMN_CSG_list_tb:\"<img src=\"./img/tick.png\"> PLMN CSG 列表\",\
					in_id_request1_tb:\"<input type=\"button\" id=\"btnList\" class=\"pbutton\" value=\"请求\" onClick=\"plmnCSGList()\">\",\
					in_id_plmn_csg2_tb:\"<img src=\"./img/tick.png\"> PLMN CSG 选择\",\
					in_id_request2_tb:\"<input type=\"button\" id=\"btnSelectReq\" class=\"pbutton\" value=\"请求\" onClick=\"plmnCSGSelect()\">	\",\
					in_id_csg_id_tb:\"CSG ID\",\
					in_id_plmn_id_tb:\"PLMN ID\",\
					in_id_plmn_csg_csgl_tb:\"<img src=\"./img/tick.png\"> PLMN CSG 获取 CSGL\",\
					in_id_gat_tb:\"<input type=\"button\" id=\"btnGetCSGL\" class=\"pbutton\" value=\"获取\" onClick=\"plmnCSGGetCSGL()\">\",\
					in_id_plmn_csg_acsgl_tb:\"<img src=\"./img/tick.png\"> PLMN CSG 设置 ACSGL\",\
					in_id_setting_tb:\"<input type=\"button\" id=\"btnSetACSGL\" class=\"pbutton\" value=\"设置\" onClick=\"plmnCSGSetACSGL()\">\",\
					in_id_serch_usim_tb:\"查询USIM\",\
					in_id_index_tb:\"记录索引\",\
					in_id_csg_tb:\"CSG 类型IND\",\
					in_id_csg_ind_tb:\"CSG 名称IND\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_list_request:\"PLMN CSG 列表请求失败!!\",\
					str_alert_fill_blanks:\"请填空\",\
					str_alert_PLMN_ID:\"无效的 PLMN ID\",\
					str_alert_plmnselect_success:\"PLMN CSG 查询请求成功!!\",\
					str_alert_plmnselect_fail:\"PLMN CSG 查询请求失败!!\",\
					str_alert_request_fail:\"PLMN CSG GET CSGL 请求失败!!\",\
					str_alert_invalid_id:\"无效的 PLMN ID\",\
					str_alert_plmn_request_success:\"PLMN CSG 设置 ACSGL 请求成功!!\",\
					str_alert_plmn_request_fail:\"PLMN CSG 设置 ACSGL 请求失败!!\",\
				},\
			},\
			h_ap_access:\
			{\
				\title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_wifi_setting:\"WiFi 设置\",\
					in_id_access_list1_tb:\"<img src=\"./img/tick.png\">&nbsp; 访问表\",\
					in_id_ap_instance_tb:\"AP 例子\",\
					in_id_access_policy_tb:\"存取策略\",\
					in_id_off_tb:\"关闭\",\
					in_id_allow_tb:\"允许\",\
					in_id_reject_tb:\"拒绝\",\
					in_id_mac_Search_tb:\"连接物理地址搜索\",\
					in_id_access_list2_tb:\"访问表\",\
					in_id_no_tb:\"编号\",\
					in_id_mac_address_tb:\"物理地址(外部克隆)\",\
				in_id_add_new_tb:\"<input type=\"button\" class=\"pbutton\" value=\"添加 新的\" onclick=\"addAccessEntry('')\" }>\",\
					in_id_applies_tb:\"<input type=\"button\" id=\"btnwifiaccess\" class=\"pbutton\" value=\"应用\" onclick=\"wifiSetAccessList()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_enable_ap:\"不能发现使能 AP.\n 请创建 AP 在 AP 设置页面.\",\
					str_alert_setting_change:\"Wifi 设置改变成功\n需要重启让值生效\",\
					str_alert_enable_ap:\"不能添加更多的 MAC 地址\",\
					str_alert_mac_length:\"MAC地址长度必须为12位!\",\
					str_alert_Wifi_changed:\"Wifi设置改变成功\",	\
					str_alert_AP_restarted:\Wifi AP 在重新启动\",\
					str_alert_Remove:\"移除\",\
				},				\
			},\
			h_upload:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_file_upload_tb:\"上传文件\",\
					in_id_file_upload1_tb:\"<img src=\"./img/tick.png\">&nbsp; 将文件上传到系统\",\
					in_id_locate_tb:\"设备上的位置\",\
					in_id_upload_file_tb:\"要上传的文件\",\
					in_id_apply_upload_tb:\"<input type=\"button\" class=\"pbutton\" name=\"upload\" id=\"upload\" value=\"上传\" onclick=\"startUpload()\">\",				\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
						str_alert_chose_file_upload:\"请选择要上传的文件\",\
				},				\
			},\
			h_nvlte:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{		\
					in_id_sys_lte_tb:\"系统NV - LTE\",\
					in_id_info_tb:\"信息\",\
					in_id_board_tb:\"板卡\",\
					in_id_RF_tb:\"RF计算\",\
					in_id_ET_tb:\"ET计算\",\
					in_id_TC_tb:\"TC计算\",\
					in_id_VENDOR_tb:\"厂商\",\
					in_id_net_info_tb:\"网络信息\",\
					in_id_safety_tb:\"安全信息\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},				\
			},\
			h_nvcommon:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{				\
					in_id_syscommon_tb:\"系统通用NV\",\
					in_id_board_set_tb:\"板卡配置\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				},				\
			},\
			h_wifiapwps:\
			{\
				innerHTML:\
				{				\
					in_id_wps_set_tb:\"WPS设置\",\
					in_id_wps_setting_tb:\"<th colspan=\"2\"><img src=\"./img/tick.png\">&nbsp; WPS设置</th>\",\
					in_id_AP_tb:\"AP实例\",\
					in_id_ssid_name_tb:\"网络名称(SSID)\",\
					in_id_certificate_tb:\"认证\",\
					in_id_data_tb:\"数据加密\",\
					in_id_network_key:\"网络密钥\",\
					in_id_reset_refresh_tb:\"<input type=\"button\" class=\"pbutton\" id=\"btn_reset\" value=\"WPS重置\" onclick=\"wifiRestartApd()\"><input type=\"button\" class=\"pbutton\" id=\"btn_refresh\" value=\"刷新\" onclick=\"wifiGetSetting()\"><input type=\"button\" class=\"pbutton\" id=\"btn_apply\" value=\"应用\" onclick=\"wifiSetSetting()\">\",\
					in_id_registrar1_tb:\"<img src=\"./img/tick.png\">&nbsp; 对于内部注册</th>\",\
					in_id_connect_tb:\"<input type=\"button\" id=\"btn_registrar_connect\" value=\"WPS连接\" onclick=\"wps_connect()\">\",\
					in_id_push_button_tb:\"<input type=\"hidden\" id=\"wps_connect_type\" value=\"1\"><input type=\"radio\" name=\"wps_connect_type_radio\" value=\"0\" checked onclick=\"change_wps_method();\">PBC: 按钮配置 (PBC)<br/><input type=\"radio\" name=\"wps_connect_type_radio\" value=\"1\" onclick=\"change_wps_method();\">PIN : 设置PIN的PIN - STA 连接<input type=\"text\" class=\"inputtext\" id=\"sta_pin\" style=\"width:80px\">\",\
					in_id_registrar2_tb:\"<img src=\"./img/tick.png\">&nbsp; 对于外部的注册\",\
					in_id_update_tb:\"AP PIN <input type=\"text\" class=\"inputtext\" id=\"ap_pin\" style=\"width:80px\" readonly><input type=\"button\" id=\"btn_ap_pin_renew\" value=\"更新\" onclick=\"wps_ap_pin_renew()\">\",\
					in_id_state_tb:\"<img src=\"./img/tick.png\">&nbsp; WPS 状态\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
				str_alert_wifi_wps:\"Wifi WPS 设置改变成功\",\
				str_alert_wps_reset:\"WPS 重置完成,重新加载当前页面\",\
				str_alert_invaild:\"WPS STA PIN 是无效的\",	\
				},\
			},\
			h_wpssetting:\
			{\
				innerHTML:\
				{				\
					in_id_WPS_Setting_tb:\"WPS 设置\",\
					in_id_WPS_Enable_tb:\"<img src=\"./img/tick.png\">&nbsp; WPS 使能\",\
					in_id_WPS_Enable1_tb:\"WPS 使能\",\
					in_id_disable_enable_tb:\"<select class=\"selectbox\" id=\"wps_enable\" style=\"width:150px\" ><option value=\"0\">禁止</option><option value=\"1\">使能</option></select>\",\
					in_id_Apply1_tb:\"<input type=\"button\" class=\"pbutton\" id=\"wps_enable_switch\" value=\"应用\" onclick=\"EnableWPS()\">\",	\
					in_id_wps_setting1_tb:\"<img src=\"./img/tick.png\">&nbsp; WPS设置\",\
					in_id_WPS_Mode_tb:\"WPS模式\",\
					in_id_WPS_Pin_tb:\"WPS Pin 模式\",\
					in_id_manual_auto_tb:\"<select class=\"selectbox\" id=\"generate_pin_type\" style=\"width:150px\" onchange=selectPinType()><option value=\"0\">手动</option><option value=\"1\">自动</option><option value=\"2\">客户端 pin</option></select>\",\
					in_id_Pin_tb:\"Pin\",\
					in_id_Generate_PIN_value_tb:\"<input type=\"number\" oninput=\"if(value.length>8) value=value.slice(0,8)\" class=\"inputtext\" id=\"ssid_wps_pin\" style=\"width:150px\"><input type=\"button\" id=\"btn_generate\" value=\"产生一个pin值\" onclick=\"generate_wps_ap_pin();\">\",\
					in_id_Connect_WPS_tb:\"<input type=\"button\" class=\"pbutton\" id=\"connectWps\" value=\"连接 WPS\" onclick=\"connect_wps()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_pin_length:\"PIN 长度必须是 8!\",\
					str_alert_Wifi_changed:\"Wifi 设置改变成功\",\
					str_alert_Applied_WPS:\"已成功应用wps pin！必须在2分钟内运行受Wi-Fi保护的安装程序\",\
					str_alert_WPS_invaild:\"WPS AP PIN 是无效的\",\
					str_alert_Start_PBC:\"启动PBC成功！您必须在2分钟内运行受Wi-Fi保护的安装程序\",\
				},\
			},\
			h_wcdmasettig:\
			{\
				innerHTML:\
				{				\
					in_id_WCDMA1_tb:\"WCDMA设置\",\
					in_id_WCDMA2_tb:\"<img src=\"./img/tick.png\">&nbsp; WCDMA开启\",\
					in_id_enable_tb:\"使能\",\
					in_id_enable_disable_tb:\"<select id=\"wcdma_enable\" class=\"selectbox\" style=\"width:100\"><option value=0>关闭</option><option value=1>打开</option></select>\",\
					in_id_WCDMA3_tb:\"<img src=\"./img/tick.png\">&nbsp;WCDMA设置\",\
					in_id_number_tb:\"数字\",\
					in_id_applies_tb:\"<input type=\"button\" class=\"pbutton\" name=\"ButtonApply\" value=\"应用\" onclick=\"wcdmaSetSetting()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_setting_change:\"设置已经改变.\n下次连接后应用\",\
				},\
			},\
			h_wifistasetting:\
			{\
				innerHTML:\
				{\
					in_id_wifi_tb:\"WiFi设置\",\
					in_id_sta_setting_tb:\"<img src=\"./img/tick.png\">&nbsp; STA设置\",\
					in_id_enable_tb:\"使能\",\
					in_id_disable_enable_tb:\"<select class=\"selectbox\" id=\"enable\" style=\"width:150px\"><option value=\"0\">禁用</option><option value=\"1\">使能</option></select>\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" value=\"应用\" onclick=\"wifiSetSetting()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_setting_change:\"Wifi 设置改变成功 \n需要重启让值生效\",\
				},\
			},\
			h_telnet:\
			{\
				title:\"系统信息\",\
				innerHTML:\
				{\
					in_id_Telnet1_tb:\"远程登录\",\
					in_id_Telnet2_tb:\"<img src=\"./img/tick.png\">&nbsp; 远程登录:\",\
					in_id_enable_tb:\"使能\",\
					in_id_off_on_tb:\"<input type=\"radio\" name=\"enableTelnet\" id=\"enableTelnet\" value=\"0\">关闭&nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"enableTelnet\" id=\"enableTelnet\" value=\"1\">打开&nbsp;&nbsp;&nbsp;\",\
					in_id_apply_tb:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"SetTelnetMode()\">\",\
				},\
				value:\
				{\
				},\
				js_string:\
				{\
					str_alert_Setting_changed:\"<input type=\"button\" class=\"pbutton\" id=\"Command\" data-loading-text=\"Saving...\" value=\"应用\" onclick=\"SetTelnetMode()\">\",\
				},\
			},\
}\
]\
}\
"};

#else
{"\
info:[\{\
userid:\"admin\",\
name:\"admin\",\
},\
{\
userid:\"administrator\",\
name:\"administrator\",\
}\
]\
"};
#endif

static void updateLanguageConf()
{
	system ("ucfg get config language > /tmp/language.conf");
}

static int GetLanguage(llist entries, int set)
{


#if 0

if (set == 0)
{
	CGI_XML_VALUE("LANGUAGE", langbuf);
} 

CGI_XML_VALUE("LANGUAGE", get_value);

#elif 1
	char ini_file[256];
	char get_value[LENGTH_INI_KEY_AND_VALUE] = {0,};
	char *key;
	int ret;
	char tmp[256]="";
	
	
	if (set == 0)
	{
		sprintf(ini_file, "/tmp/language.conf");
		key = "ENABLE";
		if (0 > GetPrivateProfileString(
					"", // No section
					key,
					"0",
					get_value,
					sizeof(get_value) - 1,
					ini_file)) {
			return -1;
		}
		CGI_XML_VALUE("LANGUAGE", get_value);
	

	//	memset(get_value,0,sizeof(get_value));
	}
#else

if (set == 0)
{
	CGI_XML_VALUE("LANGUAGE", get_value);
}


#endif

	return 0;
}	


#if 1
static int SetStatus(llist entries, int set)
{
	char *val;
	val = cgi_val(entries, "LANG");
	write_ucfg_xml(CONF_BLK, "/language/ENABLE", val);
	updateLanguageConf();
	return 0;
}

static int GetStatus(llist entries, int set)
{
	char cmd_str[256];
	char ini_file[256];
	char get_value[LENGTH_INI_KEY_AND_VALUE] = {0,};
	char *key;
	char ipaddress[32];
	char val_set[32];
	char *val;
	
	if (set == 0)
	{
		sprintf(ini_file, "/tmp/language.conf");
		key = "ENABLE";
		if (0 > GetPrivateProfileString(
					"", // No section
					key,
					"0",
					get_value,
					sizeof(get_value) - 1,
					ini_file)) {
			return -1;
		}
		
	CGI_XML_VALUE("LANGUAGE", get_value);
	}
	return 0;
}



#endif

#if 1

static int GetLanguagebuf(llist entries, int set)
{	
	char cmd_str[256];
	char ini_file[256];
	char apn_str[32];
	char get_value[LENGTH_INI_KEY_AND_VALUE] = {0,};
	char *key;
	int iApn = 0;
	int apnLength;
	sprintf(ini_file, "/tmp/apntable_default_%d", rand());
	sprintf(cmd_str, "ucfg get config apntable_default > %s", ini_file);
	system(cmd_str); 
	
	
	
	
			/*added by cghui 20190817*/
		key = "use";
		if (0 > GetPrivateProfileString(
			apn_str, // No section
			key,
			"0",
			get_value,
			sizeof(get_value) - 1,
			ini_file)) {
			return -1;
		}
		CGI_XML_VALUE("USE", get_value);
		/*ended by cghui 20190817*/

	if (set == 0)
	{
		//CGI_XML_VALUE("LANGUAGE", langbuf);
		CGI_XML_VALUE("LANGUAGEBUF", langbuf+1);
	}
	
	return 0;
}

#endif

int main()
{
		llist entries;
		int ret = 0;
		int init_ucfg_ret = -1;
		char* command;
		
		list_create(&entries);
		CGI_XML_BEGIN();
		init_ucfg_ret = init_ucfg();
		if(init_ucfg_ret < 0){
			CGI_XML_VALUE("Error", "%s", "init_ucfg Fail");
			goto out;
		}
	
		ret = read_cgi_input(&entries);
		if (ret)
		{
			command = cgi_val(entries, CGI_REQUEST_COMMAND);
			if (command == NULL)
			{
				CGI_XML_VALUE("Error", "%s", "NoCommand");
			}
			else if (!strcmp(command, "Language"))
			{
				pthread_mutex_lock(&cgi_lock);
	
				GetLanguage(entries, 0);
				pthread_mutex_unlock(&cgi_lock);
	
			}
#if 1			
			else if (!strcmp(command, "GetLanguageAllSetting"))
			{
				pthread_mutex_lock(&cgi_lock);
		
				GetStatus(entries, 0);

				pthread_mutex_unlock(&cgi_lock);
		
			}
#endif
#if 1   
		else if (!strcmp(command, "Languagebuf"))
		{
			pthread_mutex_lock(&cgi_lock);

			GetLanguagebuf(entries, 0);
			pthread_mutex_unlock(&cgi_lock);
		}
#endif		
			else if (!strcmp(command, "SetlanguageEnable") )
			{
				SetStatus(entries, 0);
			}
			else
			{
				CGI_XML_VALUE("Error", "%s", "CGI Unknown Command");
			}
		}
	
	out:
		if(init_ucfg_ret == 0)
			deinit_ucfg();
		CGI_XML_END();
		list_clear(&entries);
		
		pthread_mutex_destroy(&cgi_lock);
		pthread_cond_destroy(&cgi_cond);
		
		return 0;
}


