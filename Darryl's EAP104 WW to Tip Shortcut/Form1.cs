using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WPCreater
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent(); //This function is needed to pretty much setup up the windows form application.
        }

/*Note to viewers: This function below creates the HTML and CSS files in the current directory by
 writing the information required for creating a HTML and CSS file, as well as utilizing user inputs to help customize it. The function begins
 once the button labled "Make" is clicked. 
*/
        private void button1_Click(object sender, EventArgs e)
        {
			string hold = null;
			string output = null;
			int linecounter = 1;
			int i;
			string SN1, SN2, SN3, SN4, SN5, MAC1, MAC2, MAC3, MAC4, MAC5, space1, space2, space3, space4;
			SN1 = SN2 = SN3 = SN4 = SN5 = MAC1 = MAC2 = MAC3 = MAC4 = MAC5 = space1 = space2 = space3 = space4 = null;
			//string[] stringlist = {SN1, MAC1, space1, SN2, MAC2, space2, SN3, MAC3, space3, SN4, MAC4, space4, SN5, MAC5};


			hold = textBox1.Text;
			for (i = 0; i < hold.Length; i++)
			{
				if (hold[i] == '\r')
					continue;
				if (hold[i] == '\n')
				{
					linecounter++;
					continue;
				}
				if (hold[i] != '\n')
				{
					if (linecounter == 1)
						SN1 += hold[i];
					if (linecounter == 2)
						MAC1 += hold[i];
					if (linecounter == 3)
						space1 += hold[i];
					if (linecounter == 4)
						SN2 += hold[i];
					if (linecounter == 5)
						MAC2 += hold[i];
					if (linecounter == 6)
						space2 += hold[i];
					if (linecounter == 7)
						SN3 += hold[i];
					if (linecounter == 8)
						MAC3 += hold[i];
					if (linecounter == 9)
						space3 += hold[i];
					if (linecounter == 10)
						SN4 += hold[i];
					if (linecounter == 11)
						MAC4 += hold[i];
					if (linecounter == 12)
						space4 += hold[i];
					if (linecounter == 13)
						SN5 += hold[i];
					if (linecounter == 14)
						MAC5 += hold[i];


				}


				if (linecounter == 15)
					break;
			}

			output = String.Format(@"====================================================================================



					 INSTRUCTIONS FOR

			CONVERTING EAP104-WW > EAP104 - T(TIP OpenWiFi)



====================================================================================
HELPFUL OPENWRT COMMANDS:

fw_printenv	> CHECK ALL VARIABLES SET


============================================================================================
		### STEP 1 : ENTER U-BOOT
============================================================================================



PRESS ANY KEY TO STOP AUTOBOOT (Enter U-Boot)



============================================================================================
		### STEP 3 : SET AP IP ADDRESS && TFTP SERVER IP ADDRESS && PING
============================================================================================


setenv ipaddr 10.10.0.70
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.71
setenv serverip 10.10.0.130
ping 10.10.0.130


setenv ipaddr 10.10.0.72
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.73
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.74
setenv serverip 10.10.0.130
ping 10.10.0.130




============================================================================================
		### STEP 4 : LOAD BASE IMAGE
============================================================================================







tftpboot norplusnand-ipq5018-single-eap104-20220427.img
  
  

imgaddr=$fileaddr && source $imgaddr:script
    


sf probe
    


sf erase 0x1e0000 0x10000
    


reset





! ! ! PRESS ANY KEY TO STOP AUTOBOOT (Enter U-Boot) ! ! !









============================================================================================
		### STEP 5 : SET AP IP ADDRESS && TFTP SERVER IP ADDRESS && PING
============================================================================================


setenv ipaddr 10.10.0.70
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.71
setenv serverip 10.10.0.130
ping 10.10.0.130


setenv ipaddr 10.10.0.72
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.73
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.74
setenv serverip 10.10.0.130
ping 10.10.0.130




============================================================================================
		### STEP 6 : LOAD OpenWRT IMAGE FILE 
============================================================================================


tftpboot openwrt-ipq807x-edgecore_eap104-squashfs-nand-factory.bin && imgaddr=$fileaddr
	 


imxtract $imgaddr ubi && nand device 0
    


nand erase 0x00080000 0x03e00000 
   


nand write $fileaddr 0x00080000 $filesize 
    


nand erase 0x3e80000 0x3e00000
    


nand write $fileaddr 0x3e80000 $filesize



reset  


! ! ! PRESS ANY KEY TO STOP AUTOBOOT ! ! !




============================================================================================
		### STEP 7a : WRITE UBOOT ENVIRONMENT AND SERIAL DETAILS
============================================================================================


setenv bootcount 1  

setenv active 1  

setenv upgrade_available 0  

setenv SN {0}
setenv SN {2}
setenv SN {4}
setenv SN {6}
setenv SN {8}


saveenv 


reset 


! ! ! PRESS ANY KEY TO STOP AUTOBOOT (Enter U-Boot) ! ! !




=============================================================================================================
		### STEP 7b : Use the following command to check the information of SN and uboot environment. 
=============================================================================================================



printenv SN 

printenv bootcount 

printenv active 

printenv upgrade_available


#### OUTPUT EXAMPLE ######

IPQ5018# printenv SN
SN=EC2324003814
IPQ5018#
SN=EC2324003814
IPQ5018# printenv bootcount
bootcount=1
IPQ5018#
bootcount=1
IPQ5018# printenv active
active=1
IPQ5018#
active=1
IPQ5018# printenv upgrade_available
upgrade_available=0
IPQ5018#


============================================================================================
		### STEP 8 : WRITE MANUFACTURING DATA
============================================================================================


**********************************************************************
	### WRITE THE VALUES BELOW AND USE DEVICES MAC AND SN

	### ! ! ! MAKE SURE TO ENTER CORRECT MAC AND SERIAL ! ! !

	### ! ! ! MAKE SURE TO ENTER CORRECT MAC AND SERIAL ! ! !

	### ! ! ! MAKE SURE TO ENTER CORRECT MAC AND SERIAL ! ! !

**********************************************************************

setenv sku EAP104 \(T\)

setenv model EAP104 

setenv model_revision R01 

setenv serial_number {0}
setenv serial_number {2}
setenv serial_number {4}
setenv serial_number {6}
setenv serial_number {8}


setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{1}\"",\""VN\"":\""EC\"",\""SN\"":\""{0}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{3}\"",\""VN\"":\""EC\"",\""SN\"":\""{2}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{5}\"",\""VN\"":\""EC\"",\""SN\"":\""{4}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{7}\"",\""VN\"":\""EC\"",\""SN\"":\""{6}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{9}\"",\""VN\"":\""EC\"",\""SN\"":\""{8}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}

setenv manufacturer_name EC 


setenv manufacturer_date 01-07-2023 


setenv manufacturer_url www.edge-core.com 


setenv model_description ""802.11ax Dual-Band Enterprise Access Point"" 


setenv reference_design ""QCA AP-MP03.5-C1"" 


setenv certification_region US 


setenv mac_address ""{1}""
setenv mac_address ""{3}""
setenv mac_address ""{5}""
setenv mac_address ""{7}""
setenv mac_address ""{9}""


saveenv 


reset 


**********************************************************************
	### LET AP BOOT TO APNOS (OpenWRT)
	### CHECK THE VARIABLES WE JUST SET
**********************************************************************

fw_printenv		note to self > adjust this to only specified values


============================================================================================
		### STEP 9 : WRITE CERTIFICATES
============================================================================================



**********************************************************************
	### Reset the device to factory default and reboot the device 
**********************************************************************



firstboot -y && reboot 



**********************************************************************
	### Check ucentral.active exists in the /etc/ucentral folder. 
	### Please wait for 10 seconds and retry 2 times.
**********************************************************************



cd /etc/ucentral 

ls -al 



**********************************************************************
	### If fails to find ucentral.active, please reset to default again, 
	### and go to Steps 2 and retry 2 times. If fails to find ucentral.active 3 
	### times, reflash the image again. 
********************************************************************* 



**********************************************************************
	### Wait until /certificates directory is mounted 
**********************************************************************

mount

**********************************************************************
	### OUTPUT BELOW:
**********************************************************************
# mount 
mtd:ubi_rootfs on /rom type squashfs (ro,relatime) 
proc on /proc type proc (rw,nosuid,nodev,noexec,noatime) 
sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,noatime) 
tmpfs on /tmp type tmpfs (rw,nosuid,nodev,noatime) 
/dev/ubi0_2 on /overlay type ubifs (rw,noatime) 
overlayfs:/overlay on / type overlay(rw,noatime,lowerdir=/,upperdir=/overlay/up
per,workdir=/overlay/work) 
tmpfs on /dev type tmpfs (rw,nosuid,relatime,size=512k,mode=755) 
devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,mode=600,ptmxmode=000) 
debugfs on /sys/kernel/debug type debugfs (rw,noatime) 
bpffs on /sys/fs/bpf type bpf (rw,nosuid,nodev,noexec,noatime,mode=700) 
pstore on /sys/fs/pstore type pstore (rw,noatime) 
ubi0:certificates on /certificates type ubifs (rw,relatime)	#### < THIS IS THE LINE WE ARE LOOKING FOR ####




============================================================================================
	### STEP 10 : COPY THE CERT FILES TO THE AP USING HTTP SERVER AND WGET
============================================================================================

	### CERTS ARE IN HTTP SERVER UNDER ""INDEX OF wifiap/tip_certs""
	### use wget

	### Enter /certificates



cd /certificates




**********************************************************************
	### wget the cert file
**********************************************************************

wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{1}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{3}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{5}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{7}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{9}.tar.gz
ls



**********************************************************************
	### Unpack the cert file to its 4 components (cas.pem   cert.pem  dev-id    key.pem)
**********************************************************************

tar -xzf {1}.tar.gz
tar -xzf {3}.tar.gz
tar -xzf {5}.tar.gz
tar -xzf {7}.tar.gz
tar -xzf {9}.tar.gz

ls




**********************************************************************
	### Remove tar.gz file, leaving 4 components in place (cas.pem   cert.pem  dev-id    key.pem)
**********************************************************************

rm {1}.tar.gz
rm {3}.tar.gz
rm {5}.tar.gz
rm {7}.tar.gz
rm {9}.tar.gz

ls

**********************************************************************
				EXAMPLE OUTPUT 
**********************************************************************

root@e001a6d10ff4:/certificates# wget http://10.10.0.148/html/wifiap/TIP/E001A6D
10FF4.tar.gz
Downloading 'http://10.10.0.148/html/wifiap/TIP/E001A6D10FF4.tar.gz'
Connecting to 10.10.0.148:80
Writing to 'E001A6D10FF4.tar.gz'
E001A6D10FF4.tar.gz  100% |*******************************|  4056   0:00:00 ETA
Download completed (4056 bytes)
root@e001a6d10ff4:/certificates# ls
E001A6D10FF4.tar.gz
root@e001a6d10ff4:/certificates# tar -xzf E001A6D10FF4.tar.gz
root@e001a6d10ff4:/certificates# rm E001A6D10FF4.tar.gz
root@e001a6d10ff4:/certificates# ls
cas.pem   cert.pem  dev-id    key.pem










=========================================================================================
	### STEP 11 : VERIFY CERTS AND FINALIZE
=========================================================================================



**********************************************************************
	### Sync the file and Reboot the device  
**********************************************************************



sync && sync && reboot 





**********************************************************************
	### Reset the device to factory default
**********************************************************************


firstboot -y



**********************************************************************
	### Sync the file and make sure “reboot: Power down” string exists in the console log. 
**********************************************************************


sync && sync && halt 


=========================================================================================
	### STEP 12 : UPDATE TO CURRENT STABLE RELEASE
=========================================================================================

! ! ! MAKE SURE AP IS ON 2.11 BEFORE GOING TO 3.X.X ! ! !

ping 10.10.0.148

sysupgrade http://10.10.0.148/html/wifiap/openwrt-ipq807x-edgecore_eap104-v2.11.0-squashfs-sysupgrade.tar


sysupgrade http://10.10.0.148/html/wifiap/openwrt-ipq50xx-edgecore_eap104-v3.0.1-squashfs-sysupgrade.tar


(If ""connection failed"" message appears, reboot and attempt again)



+++++++++++++++++++++++++++++++++++++++++
		LOG FILE
+++++++++++++++++++++++++++++++++++++++++


uci show ucentral	

iwinfo

cat /etc/openwrt_release 

fw_printenv 


==========================
AFTER LOG 
==========================

	#### Enter ""sync && sync && halt""

sync && sync && halt

	#### STOP the autoboot and enter U-boot (bootloader)

	#### unplug device while device is in bootloader.















", SN1, MAC1, SN2, MAC2, SN3, MAC3, SN4, MAC4, SN5, MAC5);


			StreamWriter File = new StreamWriter("./Serial&Mac.txt");
			File.Write(output);
			File.Close();

			Close(); // The file is closed denoting the successful completion of the CSS file
        }

        private void TextBox1_DragEnter(object sender, DragEventArgs e)
        {
			string hold = null;
            string output = null;
			int linecounter = 1;
			int i;
			string SN1, SN2, SN3, SN4, SN5, MAC1, MAC2, MAC3, MAC4, MAC5, space1, space2, space3, space4;			
			SN1 = SN2 = SN3 = SN4 = SN5 = MAC1 = MAC2 = MAC3 = MAC4 = MAC5 = space1 = space2 = space3 = space4 = null;
			//string[] stringlist = {SN1, MAC1, space1, SN2, MAC2, space2, SN3, MAC3, space3, SN4, MAC4, space4, SN5, MAC5};

			e.Effect = DragDropEffects.All;
			hold += e.Data.GetData(DataFormats.Text).ToString();
			for(i = 0; i < hold.Length; i++)
            {
				if (hold[i] == '\r')
					continue;
				if (hold[i] == '\n')
				{
					linecounter++;
					continue;
				}
				if (hold[i] != '\n')
				{
					if(linecounter == 1)
						SN1 += hold[i];
					if (linecounter == 2)
						MAC1 += hold[i];
					if (linecounter == 3)
						space1 += hold[i];
					if (linecounter == 4)
						SN2 += hold[i];
					if (linecounter == 5)
						MAC2 += hold[i];
					if (linecounter == 6)
						space2 += hold[i];
					if (linecounter == 7)
						SN3 += hold[i];
					if (linecounter == 8)
						MAC3 += hold[i];
					if (linecounter == 9)
						space3 += hold[i];
					if (linecounter == 10)
						SN4 += hold[i];
					if (linecounter == 11)
						MAC4 += hold[i];
					if (linecounter == 12)
						space4 += hold[i];
					if (linecounter == 13)
						SN5 += hold[i];
					if (linecounter == 14)
						MAC5 += hold[i];


				}
				
				
				if (linecounter == 15)
					break;
            }

			output = String.Format(@"====================================================================================



					 INSTRUCTIONS FOR

			CONVERTING EAP104-WW > EAP104 - T(TIP OpenWiFi)



====================================================================================
HELPFUL OPENWRT COMMANDS:

fw_printenv	> CHECK ALL VARIABLES SET


============================================================================================
		### STEP 1 : ENTER U-BOOT
============================================================================================



PRESS ANY KEY TO STOP AUTOBOOT (Enter U-Boot)



============================================================================================
		### STEP 3 : SET AP IP ADDRESS && TFTP SERVER IP ADDRESS && PING
============================================================================================


setenv ipaddr 10.10.0.70
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.71
setenv serverip 10.10.0.130
ping 10.10.0.130


setenv ipaddr 10.10.0.72
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.73
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.74
setenv serverip 10.10.0.130
ping 10.10.0.130




============================================================================================
		### STEP 4 : LOAD BASE IMAGE
============================================================================================







tftpboot norplusnand-ipq5018-single-eap104-20220427.img
  
  

imgaddr=$fileaddr && source $imgaddr:script
    


sf probe
    


sf erase 0x1e0000 0x10000
    


reset





! ! ! PRESS ANY KEY TO STOP AUTOBOOT (Enter U-Boot) ! ! !









============================================================================================
		### STEP 5 : SET AP IP ADDRESS && TFTP SERVER IP ADDRESS && PING
============================================================================================


setenv ipaddr 10.10.0.70
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.71
setenv serverip 10.10.0.130
ping 10.10.0.130


setenv ipaddr 10.10.0.72
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.73
setenv serverip 10.10.0.130
ping 10.10.0.130

setenv ipaddr 10.10.0.74
setenv serverip 10.10.0.130
ping 10.10.0.130




============================================================================================
		### STEP 6 : LOAD OpenWRT IMAGE FILE 
============================================================================================


tftpboot openwrt-ipq807x-edgecore_eap104-squashfs-nand-factory.bin && imgaddr=$fileaddr
	 


imxtract $imgaddr ubi && nand device 0
    


nand erase 0x00080000 0x03e00000 
   


nand write $fileaddr 0x00080000 $filesize 
    


nand erase 0x3e80000 0x3e00000
    


nand write $fileaddr 0x3e80000 $filesize



reset  


! ! ! PRESS ANY KEY TO STOP AUTOBOOT ! ! !




============================================================================================
		### STEP 7a : WRITE UBOOT ENVIRONMENT AND SERIAL DETAILS
============================================================================================


setenv bootcount 1  

setenv active 1  

setenv upgrade_available 0  

setenv SN {0}
setenv SN {2}
setenv SN {4}
setenv SN {6}
setenv SN {8}


saveenv 


reset 


! ! ! PRESS ANY KEY TO STOP AUTOBOOT (Enter U-Boot) ! ! !




=============================================================================================================
		### STEP 7b : Use the following command to check the information of SN and uboot environment. 
=============================================================================================================



printenv SN 

printenv bootcount 

printenv active 

printenv upgrade_available


#### OUTPUT EXAMPLE ######

IPQ5018# printenv SN
SN=EC2324003814
IPQ5018#
SN=EC2324003814
IPQ5018# printenv bootcount
bootcount=1
IPQ5018#
bootcount=1
IPQ5018# printenv active
active=1
IPQ5018#
active=1
IPQ5018# printenv upgrade_available
upgrade_available=0
IPQ5018#


============================================================================================
		### STEP 8 : WRITE MANUFACTURING DATA
============================================================================================


**********************************************************************
	### WRITE THE VALUES BELOW AND USE DEVICES MAC AND SN

	### ! ! ! MAKE SURE TO ENTER CORRECT MAC AND SERIAL ! ! !

	### ! ! ! MAKE SURE TO ENTER CORRECT MAC AND SERIAL ! ! !

	### ! ! ! MAKE SURE TO ENTER CORRECT MAC AND SERIAL ! ! !

**********************************************************************

setenv sku EAP104 \(T\)

setenv model EAP104 

setenv model_revision R01 

setenv serial_number {0}
setenv serial_number {2}
setenv serial_number {4}
setenv serial_number {6}
setenv serial_number {8}


setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{1}\"",\""VN\"":\""EC\"",\""SN\"":\""{0}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{3}\"",\""VN\"":\""EC\"",\""SN\"":\""{2}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{5}\"",\""VN\"":\""EC\"",\""SN\"":\""{4}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{7}\"",\""VN\"":\""EC\"",\""SN\"":\""{6}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}
setenv qr_code \{{\""DT\"":\""ap\"",\""DM\"":\""{9}\"",\""VN\"":\""EC\"",\""SN\"":\""{8}\"",\""MN\"":\""EAP104\"",\""HW\"":\""R01\""\}}

setenv manufacturer_name EC 


setenv manufacturer_date 01-07-2023 


setenv manufacturer_url www.edge-core.com 


setenv model_description ""802.11ax Dual-Band Enterprise Access Point"" 


setenv reference_design ""QCA AP-MP03.5-C1"" 


setenv certification_region US 


setenv mac_address ""{1}""
setenv mac_address ""{3}""
setenv mac_address ""{5}""
setenv mac_address ""{7}""
setenv mac_address ""{9}""


saveenv 


reset 


**********************************************************************
	### LET AP BOOT TO APNOS (OpenWRT)
	### CHECK THE VARIABLES WE JUST SET
**********************************************************************

fw_printenv		note to self > adjust this to only specified values


============================================================================================
		### STEP 9 : WRITE CERTIFICATES
============================================================================================



**********************************************************************
	### Reset the device to factory default and reboot the device 
**********************************************************************



firstboot -y && reboot 



**********************************************************************
	### Check ucentral.active exists in the /etc/ucentral folder. 
	### Please wait for 10 seconds and retry 2 times.
**********************************************************************



cd /etc/ucentral 

ls -al 



**********************************************************************
	### If fails to find ucentral.active, please reset to default again, 
	### and go to Steps 2 and retry 2 times. If fails to find ucentral.active 3 
	### times, reflash the image again. 
********************************************************************* 



**********************************************************************
	### Wait until /certificates directory is mounted 
**********************************************************************

mount

**********************************************************************
	### OUTPUT BELOW:
**********************************************************************
# mount 
mtd:ubi_rootfs on /rom type squashfs (ro,relatime) 
proc on /proc type proc (rw,nosuid,nodev,noexec,noatime) 
sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,noatime) 
tmpfs on /tmp type tmpfs (rw,nosuid,nodev,noatime) 
/dev/ubi0_2 on /overlay type ubifs (rw,noatime) 
overlayfs:/overlay on / type overlay(rw,noatime,lowerdir=/,upperdir=/overlay/up
per,workdir=/overlay/work) 
tmpfs on /dev type tmpfs (rw,nosuid,relatime,size=512k,mode=755) 
devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,mode=600,ptmxmode=000) 
debugfs on /sys/kernel/debug type debugfs (rw,noatime) 
bpffs on /sys/fs/bpf type bpf (rw,nosuid,nodev,noexec,noatime,mode=700) 
pstore on /sys/fs/pstore type pstore (rw,noatime) 
ubi0:certificates on /certificates type ubifs (rw,relatime)	#### < THIS IS THE LINE WE ARE LOOKING FOR ####




============================================================================================
	### STEP 10 : COPY THE CERT FILES TO THE AP USING HTTP SERVER AND WGET
============================================================================================

	### CERTS ARE IN HTTP SERVER UNDER ""INDEX OF wifiap/tip_certs""
	### use wget

	### Enter /certificates



cd /certificates




**********************************************************************
	### wget the cert file
**********************************************************************

wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{1}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{3}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{5}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{7}.tar.gz
wget http://10.10.0.148/html/wifiap/tip_certs/pavlov_7_10_24/{9}.tar.gz
ls



**********************************************************************
	### Unpack the cert file to its 4 components (cas.pem   cert.pem  dev-id    key.pem)
**********************************************************************

tar -xzf {1}.tar.gz
tar -xzf {3}.tar.gz
tar -xzf {5}.tar.gz
tar -xzf {7}.tar.gz
tar -xzf {9}.tar.gz

ls




**********************************************************************
	### Remove tar.gz file, leaving 4 components in place (cas.pem   cert.pem  dev-id    key.pem)
**********************************************************************

rm {1}.tar.gz
rm {3}.tar.gz
rm {5}.tar.gz
rm {7}.tar.gz
rm {9}.tar.gz

ls

**********************************************************************
				EXAMPLE OUTPUT 
**********************************************************************

root@e001a6d10ff4:/certificates# wget http://10.10.0.148/html/wifiap/TIP/E001A6D
10FF4.tar.gz
Downloading 'http://10.10.0.148/html/wifiap/TIP/E001A6D10FF4.tar.gz'
Connecting to 10.10.0.148:80
Writing to 'E001A6D10FF4.tar.gz'
E001A6D10FF4.tar.gz  100% |*******************************|  4056   0:00:00 ETA
Download completed (4056 bytes)
root@e001a6d10ff4:/certificates# ls
E001A6D10FF4.tar.gz
root@e001a6d10ff4:/certificates# tar -xzf E001A6D10FF4.tar.gz
root@e001a6d10ff4:/certificates# rm E001A6D10FF4.tar.gz
root@e001a6d10ff4:/certificates# ls
cas.pem   cert.pem  dev-id    key.pem










=========================================================================================
	### STEP 11 : VERIFY CERTS AND FINALIZE
=========================================================================================



**********************************************************************
	### Sync the file and Reboot the device  
**********************************************************************



sync && sync && reboot 





**********************************************************************
	### Reset the device to factory default
**********************************************************************


firstboot -y



**********************************************************************
	### Sync the file and make sure “reboot: Power down” string exists in the console log. 
**********************************************************************


sync && sync && halt 


=========================================================================================
	### STEP 12 : UPDATE TO CURRENT STABLE RELEASE
=========================================================================================

! ! ! MAKE SURE AP IS ON 2.11 BEFORE GOING TO 3.X.X ! ! !

ping 10.10.0.148

sysupgrade http://10.10.0.148/html/wifiap/openwrt-ipq807x-edgecore_eap104-v2.11.0-squashfs-sysupgrade.tar


sysupgrade http://10.10.0.148/html/wifiap/openwrt-ipq50xx-edgecore_eap104-v3.0.1-squashfs-sysupgrade.tar


(If ""connection failed"" message appears, reboot and attempt again)



+++++++++++++++++++++++++++++++++++++++++
		LOG FILE
+++++++++++++++++++++++++++++++++++++++++


uci show ucentral	

iwinfo

cat /etc/openwrt_release 

fw_printenv 


==========================
AFTER LOG 
==========================

	#### Enter ""sync && sync && halt""

sync && sync && halt

	#### STOP the autoboot and enter U-boot (bootloader)

	#### unplug device while device is in bootloader.















", SN1, MAC1, SN2, MAC2, SN3, MAC3, SN4, MAC4, SN5, MAC5);


			StreamWriter File = new StreamWriter("./Serial&Mac.txt");
File.Write(output);
File.Close();
			Close();
		}
    }
}
