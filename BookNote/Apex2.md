# Apex

https://key08.com/index.php/game_anticheat.html

https://bbs.pediy.com/thread-126933.htm



a private um cheat

kernel driver with undetectable communication

Will pretty much do the job. If you can read and write physical memory too even better



`mmcopyvirtualmemory` is not detected, i have been using it since apex release in my driver and ive never been banned. they cant outright ban you for this, but they will probably flag you/use it in some kind of points system to ban for (ie using an overlay as well, etc)



## novak80

```c++
// glow 只需要这两个基址
uint64_t EntityList = 0x18DA2A8;
uint64_t LocalPlayer = 0x1C89868;
// 最多再添下边一个
uint64_t LocalEntityHandle = 0x1057a84;
```





### glow crashing apex

been cheating since like 3 days after apex released. been lvl 500 for a long time. I **only use glow** as I have very good natural aim. Have been predator every season. I am in the same boat as casual though, I am still using **mmcopyvirtualmemory** but still am not banned. I do not believe they will ban you for using this alone, but that it could be a contributing factor in some kind of points system they use for bans. using a personal **driver** created **from scratch** with a **non public communication** method. i dont even bother to xor strings or anything either lol



so for some reason my **external** glow is causing apex to crash at random times. sometimes i can play 3 games with no issues and other times it crashes on the first game in 20 seconds. anyone have any experience with this? I am not quite sure what is causing it to crash, there is no error the game just closes. I do not get the issue when playing without the cheat

```c++
write<bool>(Entity + GLOW_ENABLE, true);
write<int>(Entity + GLOW_CONTEXT, 1);
write<float>(Entity + 0x1D0, r);
write<float>(Entity + 0x1D4, g);
write<float>(Entity + 0x1D8, b);
for (int offset = 0x2F8; offset <= 0x328; offset += 0x4)
    write<float>(Entity + offset, FLT_MAX);
write<float>(Entity + 0x33C, FLT_MAX);

impl::memory->write<bool>(Entity + 0x3E0, true);
impl::memory->write<int>(Entity + 0x350, 1);
impl::memory->write<float>(Entity + 0x1B0, r);
impl::memory->write<float>(Entity + 0x1B4, g);
impl::memory->write<float>(Entity + 0x1B8, b);
for (int offset = 0x2F8; offset <= 0x328; offset += 0x4)
    impl::memory->write<float>(Entity + offset, FLT_MAX);
impl::memory->write<float>(Entity + 0x33C, FLT_MAX);
```



O - Others \ A - Author

O： **Don't glow people when you're in the airship**. Ghetto fix is **don't glow anyone when your Z > 11000.0**.

A：tried this and I am still crashing :/



O： how many entities should i be looping through in the list if I am only highlighting players? I had it set to 10000 but I think the first 100 contain all the players?

D： set to 150



O：Are you checking if the entity is valid?

A：how do you mean valid? I am checking the identifiers of the entity are p and 1 right before writing, and making sure the entity is not = 0

O：Yeah that's what i mean. Are you playing apex on origin or steam?

A：steam



A： i think i fixed it - have played about 7 games with no crash. I added a check to not glow teammates and it seems to have solved it. going to play some more to make sure. just crashed on game 8 and then again on the first game. i have no idea what is causing this

A： i believe the glow fade offset starts at `0x2F0` not `0x2F8` and ends at `0x320`. **Since updating this i havent had a crash yet**

O：same exact issue however starting from `0x2f0` will **makes my glow flicker**

A：are you on steam or origin? I get **no flicker and am on steam**

O：originn.. what is the difference?

A：offsets are slightly different. the ones I posted above won't work for you since I am on the steam version

O：well first of all, origin and steam are same.. i tested both, probably the issue is with the `FLT_MAX` value ..im running now another range and seems to be working



O：This is the glow I have, it doesn't crash for me

```C++
		GLOW_DURATION = 0x310,				// Offsets in: Highlight_StartOn, Highlight_SetLifeTime
			for (int l_I = 0; l_I < 60; l_I++)
			{
				DWORD64 l_BaseAddress = Driver::Read<DWORD64>(Globals->processID, Globals->moduleBase + Offsets::ENTITY_LIST + (l_I * 32));
				C_BaseEntity l_Entity = C_BaseEntity(l_BaseAddress);
 
				if (l_BaseAddress)
				{
					if ((l_Entity.GetHealth() > 0) && (l_Entity.GetHealth() < 120))
					{
						l_Entity.SetGlow(true);
						l_Entity.SetHighlightContext(1);
						l_Entity.SetColours(menuControl->glowColors[0] * 150, menuControl->glowColors[1] * 150, menuControl->glowColors[2] * 150);
						l_Entity.SetGlowDuration(FLT_MAX);
						l_Entity.SetGlowRange(FLT_MAX);
					}
				}
			}
 
void C_BaseEntity::SetGlowDuration(float p_Duration)
{
	for (int l_Offset = Offsets::GLOW_DURATION; l_Offset <= Offsets::GLOW_DURATION + 44; l_Offset += 0x4)
	{
		Driver::Write<float>(Globals->processID, m_Base + l_Offset, &p_Duration);
	}
}
```



### **BE IOCTL?**

A：I have successfully made a driver and bypassed EAC(Apex) using `IOCTL` for an **external cheat**. It seems BE is a bit more beefy these days (especially on EFT). Does anyone know if IOCTL is inherently detected by BE or if using it as long as I clear **mmunloadeddrivers** and **pidbcachetable** and dont share it should be fine? really dont wanna get HWID banned on BE lol

O1：That's all depends on how you're using IOCTL. Using IOCTL itself won't get you banned. There is basically 2 ways of using IOCTL. 这完全取决于你如何使用IOCTL。使用IOCTL本身不会让你被禁止。IOCTL基本上有2种使用方式。

\1. Most popular and most obvious - **creating device object**. This one will get you banned if your driver is **manually mapped** (which I suppose is your case), but if it's **signed** - it's ok.
\2. **Hijacking device of another legit driver**. That's depends on how you're hijacking it (there are many examples on UC and some of them are still undetected). That's what I'm using and I'm fine on both EAC & BE for more than half a year now.

A：Why would it make a difference if it is manually mapped or signed? I'm assuming they would still have some detection vector on signed drivers as well since its the same exact object为什么手动映射或签名会有所不同？我假设他们在有签名的驱动上仍然有一些检测向量，因为它是同一个对象

O1：It makes difference cause mapped drivers have no valid backed image.They will just look what's the driver is owner of this device. If it's valid and digitally signed it's ok, and if there is no image behind this, it's clearly a trace of a device from mapped driver. 这很重要，因为映射的驱动程序没有有效的备份映像。他们只会看这个设备的驱动程序是什么。如果它是有效的和数字签名的，它是没问题的，如果这后面没有图像，它显然是来自映射驱动程序的设备的痕迹。

A：hmm ok, is there a reason EAC isnt detecting this? been using this for over 6 months now on Apex without a ban (manual mapped with device) EAC没有检测到这一点是有原因的吗？已经在Apex上使用了6个多月了，没有被禁止(用设备手动映射)

O1：Cause Apex got a shitty version of EAC. If you try this, for example, on Rust or Fortnite, you'll get banned in the same day. EAC power is very dependable on money that game developers pay them. 因为Apex的EAC版本很烂。如果你尝试在Rust或《堡垒之夜》这样做，你将在当天被禁止。EAC 的权力非常依赖于游戏开发者付给他们的钱。

O2：I've been using a signed driver with IOCTL to read/write memory for about 4 or 5 years now - when ever BE went with their own kernel mode driver c2015. 我已经使用一个带有IOCTL的签名驱动程序来读/写内存大约4到5年了——当BE使用他们自己的内核模式驱动程序c2015时

O3：Just use a driver with MmCopyVirtualMemory in that case, simple enough. 在这种情况下，只需使用带有MmCopyVirtualMemory的驱动程序，就足够简单了。



>I know that EAC/BE use `MmUnloadedDrivers` to find `kdmapper`, etc. to detect but why they even do that when it's so simple to change the name of the driver? It's one line change in kdmapper. Just change the name when loading.
>
>
>
>mapped driver and IOCTL would be detected on EAC **for sure**.





O4：Is OV signing enough? Or is EV needed for keeping a private driver under the EAC and BE radar. And as long as it's signed, it's no problem using its handle for ioctl messaging? Since so many other drivers do it as well, they have to allow that? OV 证书足够么？或者 EV 是保持私人驱动下 EAC 和 BE 雷达需要。只要它被签名了，使用它的句柄来发送 `ioctl` 消息就没问题了？既然这么多其他驱动也这样做，他们必须允许吗？

O1：OV is enough, you just have to disable Secure Boot. You can create device and use IOCTL just fine if your driver is signed. OV就够了，你只需要禁用安全启动。如果您的驱动程序已签名，您可以创建设备并使用IOCTL。



> SSL证书分为DV、OV、EV三种级别证书，OV是企业型证书，需要验证企业营业执照等身份，一般只要是企业大部分申请的都是OV证书。
>
> 而EV证书是目前最高信任级别的 SSL证书。按照国际规范审查网站企业身份和域名所有权，确保网站身份的真实可靠，是最值得信赖的SSL证书。







### cheat to work in VM

I ve been trying to get the cheat to work in VM but I'm not able to access the usb from the boot menu. Can you help me ?

\1. you would need to have a solution to bypass the EAC VM checks which does not come with this
\2. the driver is detected



looks like this anticheat has `kernel level access` and probably using `obregistercallbacks`. you will need to use something with kernel access to read/write memory



---

## Noob Friendly Guide For Getting Offsets with CasualX Apexbot Dumper

https://www.unknowncheats.me/forum/apex-legends/452956-noob-friendly-guide-getting-offsets-casualx-apexbot-dumper.html

Tools Used:
As linking external websites is not allowed on Unknowncheats, you will have to google the tools yourself.

- Scylla Dumper
- Apexbot Offset Dumper by CasualX (https://github.com/CasualX/apexbot)
- Rust Programming Language

### Step 1: Dissabling EAC

Navigate to your installation folder for Apex Legends.
We need to change 2 things here:

- Rename EasyAntiCheat_launcher.exe to EasyAntiCheat_launcher2.exe
- Rename r5apex.exe to EasyAntiCheat_launcher.exe



### Step 2: Dumping the game with Scylla

- Launch `EasyAntiCheat_launcher.exe` (r5apex.exe renamed).
- Launch `Scylla_x64.exe` as administrator.
- Select `EasyAntiCheat_launcher.exe` in the active process list.
- Click `IAT Autosearch` and select `Yes`.
- Click `Get Imports`


Scylla should now look like this:

![img](assets/Fz89zB1.png)



Select `Dump` and save it somewhere you can easily acces it.



### Step3: Using Apexbot Offset Dumper

- Download Apexbot by CasualX from github.
- Extract it and navigate to apexbot-master -> offsets
- Hold Shift and left click in the folder and select open powershell window.



In the powershell window you will now enter the following command:

**Change "C:\Users\Louis\Desktop\tutorial\EasyAntiCheat_launcher_dump.exe" to the location u saved your Scylla dump.**

```powershell
cargo run --release --  "C:\Users\Louis\Desktop\tutorial\EasyAntiCheat_launcher_dump.exe"  > stdout.md
```



![img](assets/HA7krEe.png)



Congratulations you now have successfully dumped offsets from the game. The file with the offsets will be in `apexbot-master -> offsets -> stdout.md`

**Now just change the names back in Apex Legends folder (Step 1) to the old names and you can play the game again.**



# For Apex

## **IOCTL communication in Manually Mapped driver**

This driver works fine when loaded normally (through sc), but when manually mapped it loads, but the usermode client cant find the IOCTL file.

After some debugging, I found that the problem is that when the driver is manually mapped, it doesnt create the symbolic link to the device that I create.

Heres the code in DriverInitialize (called by creating a driver in DriverEntry (IoCreateDriver):

```C++
 UNICODE_STRING DeviceName = {};
    UNICODE_STRING SymbolicLinkName = {};
 
    RtlInitUnicodeString(&DeviceName, L"\\Device\\TestDriver");
 
    if (!pDriverObject)
    {
        ERR_PRINT("IS NULL\n");
        ntstatus = STATUS_FAILED_DRIVER_ENTRY;
        goto exit;
    }
 
    ntstatus = IoCreateDevice(
            pDriverObject,
            0,
            &DeviceName,
            FILE_DEVICE_UNKNOWN,
            FILE_DEVICE_SECURE_OPEN,
            TRUE,
            &pDeviceObject);
     if (!NT_SUCCESS(ntstatus))
      {
            ERR_PRINT("IoCreateDevice failed: 0x%X", ntstatus);
            goto exit;
      }
 
      RtlInitUnicodeString(&SymbolicLinkName, L"\\DosDevices\\TestDriver"); 
 
      ntstatus = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName); //this doesnt failed, but symbolic link not created (in \DosDevices\ folder)
      ERR_PRINT("CREATED SYM LINK: %wZ", usSymbolicLinkName);
      if (!NT_SUCCESS(ntstatus))
      {
            ERR_PRINT("IoCreateSymbolicLink failed: 0x%X", ntstatus);
            goto exit;
      }
```



You are gonna get clapped by BE/EAC for using IOCTLs on an manually mapped driver as they can check the device

```C++
RtlInitUnicodeString(&dev, L"\\Device\\PecesStealthDriver");
RtlInitUnicodeString(&dos, L"\\DosDevices\\PecesStealthDriver");
IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
IoCreateSymbolicLink(&dos, &dev);
```







## read process physical memory, no attach

https://www.unknowncheats.me/forum/anti-cheat-bypass/444289-read-process-physical-memory-attach.html

```c++
NTKERNELAPI
PVOID
PsGetProcessSectionBaseAddress(
	__in PEPROCESS Process
);
 
PVOID GetProcessBaseAddress(int pid) 
{
	PEPROCESS pProcess = NULL;
	if (pid == 0) return STATUS_UNSUCCESSFUL;
 
	NTSTATUS NtRet = PsLookupProcessByProcessId(pid, &pProcess);
	if (NtRet != STATUS_SUCCESS) return NtRet;
 
	PVOID Base = PsGetProcessSectionBaseAddress(pProcess);
	ObDereferenceObject(pProcess);
	return Base;
}
 
//https://ntdiff.github.io/
#define WINDOWS_1803 17134
#define WINDOWS_1809 17763
#define WINDOWS_1903 18362
#define WINDOWS_1909 18363
#define WINDOWS_2004 19041
#define WINDOWS_20H2 19569
#define WINDOWS_21H1 20180
 
DWORD GetUserDirectoryTableBaseOffset()
{
	RTL_OSVERSIONINFOW ver = { 0 };
	RtlGetVersion(&ver);
 
	switch (ver.dwBuildNumber)
	{
	case WINDOWS_1803:
		return 0x0278;
		break;
	case WINDOWS_1809:
		return 0x0278;
		break;
	case WINDOWS_1903:
		return 0x0280;
		break;
	case WINDOWS_1909:
		return 0x0280;
		break;
	case WINDOWS_2004:
		return 0x0388;
		break;
	case WINDOWS_20H2:
		return 0x0388;
		break;
	case WINDOWS_21H1:
		return 0x0388;
		break;
	default:
		return 0x0388;
	}
}
 
//check normal dirbase if 0 then get from UserDirectoryTableBas
ULONG_PTR GetProcessCr3(PEPROCESS pProcess)
{
	PUCHAR process = (PUCHAR)pProcess;
	ULONG_PTR process_dirbase = *(PULONG_PTR)(process + 0x28); //dirbase x64, 32bit is 0x18
	if (process_dirbase==0)
	{
		DWORD UserDirOffset = GetUserDirectoryTableBaseOffset();
		ULONG_PTR process_userdirbase = *(PULONG_PTR)(process + UserDirOffset);
		return process_userdirbase;
	}
	return process_dirbase;
}
ULONG_PTR GetKernelDirBase()
{
	PUCHAR process = (PUCHAR)PsGetCurrentProcess();
	ULONG_PTR cr3 = *(PULONG_PTR)(process + 0x28); //dirbase x64, 32bit is 0x18
	return cr3;
}
 
NTSTATUS ReadVirtual(uint64_t dirbase, uint64_t address, uint8_t* buffer, SIZE_T size, SIZE_T *read)
{
	uint64_t paddress = TranslateLinearAddress(dirbase, address);
	return ReadPhysicalAddress(paddress, buffer, size, read);
}
 
NTSTATUS WriteVirtual(uint64_t dirbase, uint64_t address, uint8_t* buffer, SIZE_T size, SIZE_T *written)
{
	uint64_t paddress = TranslateLinearAddress(dirbase, address);
	return WritePhysicalAddress(paddress, buffer, size, written);
}
 
NTSTATUS ReadPhysicalAddress(PVOID TargetAddress, PVOID lpBuffer, SIZE_T Size, SIZE_T *BytesRead)
{
	MM_COPY_ADDRESS AddrToRead = { 0 };
	AddrToRead.PhysicalAddress.QuadPart = TargetAddress;
	return MmCopyMemory(lpBuffer, AddrToRead, Size, MM_COPY_MEMORY_PHYSICAL, BytesRead);
}
 
//MmMapIoSpaceEx limit is page 4096 byte
NTSTATUS WritePhysicalAddress(PVOID TargetAddress, PVOID lpBuffer, SIZE_T Size, SIZE_T* BytesWritten)
{
	if (!TargetAddress)
		return STATUS_UNSUCCESSFUL;
 
	PHYSICAL_ADDRESS AddrToWrite = { 0 };
	AddrToWrite.QuadPart = TargetAddress;
 
	PVOID pmapped_mem = MmMapIoSpaceEx(AddrToWrite, Size, PAGE_READWRITE);
 
	if (!pmapped_mem)
		return STATUS_UNSUCCESSFUL;
 
	memcpy(pmapped_mem, lpBuffer, Size);
 
        *BytesWritten = Size;
	MmUnmapIoSpace(pmapped_mem, Size);
	return STATUS_SUCCESS;
}
 
#define PAGE_OFFSET_SIZE 12
static const uint64_t PMASK = (~0xfull << 8) & 0xfffffffffull;
 
uint64_t TranslateLinearAddress(uint64_t directoryTableBase, uint64_t virtualAddress) {
	directoryTableBase &= ~0xf;
 
	uint64_t pageOffset = virtualAddress & ~(~0ul << PAGE_OFFSET_SIZE);
	uint64_t pte = ((virtualAddress >> 12) & (0x1ffll));
	uint64_t pt = ((virtualAddress >> 21) & (0x1ffll));
	uint64_t pd = ((virtualAddress >> 30) & (0x1ffll));
	uint64_t pdp = ((virtualAddress >> 39) & (0x1ffll));
 
	SIZE_T readsize = 0;
	uint64_t pdpe = 0;
	ReadPhysicalAddress(directoryTableBase + 8 * pdp, &pdpe, sizeof(pdpe), &readsize);
	if (~pdpe & 1)
		return 0;
 
	uint64_t pde = 0;
	ReadPhysicalAddress((pdpe & PMASK) + 8 * pd, &pde, sizeof(pde), &readsize);
	if (~pde & 1)
		return 0;
 
	/* 1GB large page, use pde's 12-34 bits */
	if (pde & 0x80)
		return (pde & (~0ull << 42 >> 12)) + (virtualAddress & ~(~0ull << 30));
 
	uint64_t pteAddr = 0;
	ReadPhysicalAddress((pde & PMASK) + 8 * pt, &pteAddr, sizeof(pteAddr), &readsize);
	if (~pteAddr & 1)
		return 0;
 
	/* 2MB large page */
	if (pteAddr & 0x80)
		return (pteAddr & PMASK) + (virtualAddress & ~(~0ull << 21));
 
	virtualAddress = 0;
	ReadPhysicalAddress((pteAddr & PMASK) + 8 * pte, &virtualAddress, sizeof(virtualAddress), &readsize);
	virtualAddress &= PMASK;
 
	if (!virtualAddress)
		return 0;
 
	return virtualAddress + pageOffset;
}
 
 
//
NTSTATUS ReadProcessMemory(int pid, PVOID Address, PVOID AllocatedBuffer, SIZE_T size, SIZE_T* read)
{
	PEPROCESS pProcess = NULL;
	if (pid == 0) return STATUS_UNSUCCESSFUL;
 
	NTSTATUS NtRet = PsLookupProcessByProcessId(pid, &pProcess);
	if (NtRet != STATUS_SUCCESS) return NtRet;
 
	ULONG_PTR process_dirbase = GetProcessCr3(pProcess);
	ObDereferenceObject(pProcess);
 
	SIZE_T CurOffset = 0;
	SIZE_T TotalSize = size;
	while (TotalSize)
	{
 
		uint64_t CurPhysAddr = TranslateLinearAddress(process_dirbase, (ULONG64)Address + CurOffset);
		if (!CurPhysAddr) return STATUS_UNSUCCESSFUL;
 
		ULONG64 ReadSize = min(PAGE_SIZE - (CurPhysAddr & 0xFFF), TotalSize);
                SIZE_T BytesRead = 0;
		NtRet = ReadPhysicalAddress(CurPhysAddr, (PVOID)((ULONG64)AllocatedBuffer + CurOffset), ReadSize, &BytesRead);
		TotalSize -= BytesRead;
		CurOffset += BytesRead;
		if (NtRet != STATUS_SUCCESS) break;
                if(BytesRead==0) break;
	}
 
	*read = CurOffset;
	return NtRet;
}
 
NTSTATUS WriteProcessMemory(int pid, PVOID Address, PVOID AllocatedBuffer, SIZE_T size, SIZE_T* written)
{
	PEPROCESS pProcess = NULL;
	if (pid == 0) return STATUS_UNSUCCESSFUL;
 
	NTSTATUS NtRet = PsLookupProcessByProcessId(pid, &pProcess);
	if (NtRet != STATUS_SUCCESS) return NtRet;
 
	ULONG_PTR process_dirbase = GetProcessCr3(pProcess);
	ObDereferenceObject(pProcess);
 
	SIZE_T CurOffset = 0;
	SIZE_T TotalSize = size;
	while (TotalSize)
	{
		uint64_t CurPhysAddr = TranslateLinearAddress(process_dirbase, (ULONG64)Address + CurOffset);
		if (!CurPhysAddr) return STATUS_UNSUCCESSFUL;
 
		ULONG64 WriteSize = min(PAGE_SIZE - (CurPhysAddr & 0xFFF), TotalSize);
                SIZE_T BytesWritten = 0;
		NtRet = WritePhysicalAddress(CurPhysAddr, (PVOID)((ULONG64)AllocatedBuffer + CurOffset), WriteSize, &BytesWritten);
		TotalSize -= BytesWritten;
		CurOffset += BytesWritten;
		if (NtRet != STATUS_SUCCESS) break;
                if(BytesWritten==0) break;
	}
 
	*written = CurOffset;
	return NtRet;
}
```

example

Code:

```c++
char buf[64] ={0};
SIZE_T read;
ULONG_PTR Base = GetProcessBaseAddress(4321);
ReadProcessMemory(4321, Base , &buf, 64, &read);
 
process_cr3 base 0000000175391000 kernel cr3:00000000001AD000 read:2
read MZ
```

I write this to avoid kestackattachprocess detect