
// DSPIC33EV256GM104 Configuration Bit Settings

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect Bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSS2 = OFF               // Boot Segment Control Bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect Bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect Bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = DISABLE        // Alternate Interrupt Vector Table Disable Bit  (Disable Alternate Vector Table)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Code Flash Page Address Limit Bits (Boot Segment Flash Page Address Limit (0-0x1FFF))

// FOSCSEL
#pragma config FNOSC = FRC              // Initial oscillator Source Selection Bits (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Two Speed Oscillator Start-Up Bit (Start up device with user selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select Bits (XT Crystal Oscillator mode)
#pragma config OSCIOFNC = ON           // OSC2 Pin I/O Function Enable Bit (OSC2 is clock output)
#pragma config IOL1WAY = OFF                // Peripheral Pin Select Configuration Bit (Allow Only One reconfiguration)
#pragma config FCKSM = CSECMD           // Clock Switching Mode Bits (Clock Switching is enabled,Fail-safe Clock Monitor is disabled)
#pragma config PLLKEN = ON              // PLL Lock Enable Bit (Clock switch to PLL source will wait until the PLL lock signal is valid)

// FWDT
#pragma config WDTPOST = PS512          // Watchdog Timer Postscaler Bits (1:512)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler Bit (1:128)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable Bits (WDT Enabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable Bit (Watchdog timer in Non-Window Mode)
#pragma config WDTWIN = WIN25           // Watchdog Window Select Bits (WDT Window is 25% of WDT period)

// FPOR
#pragma config BOREN0 = ON              // Brown Out Reset Detection Bit (BOR is Enabled)

// FICD
#pragma config ICS = PGD2               // ICD Communication Channel Select Bits (Communicate on PGEC1 and PGED1)

// FDMTINTVL
#pragma config DMTIVTL = 0xFFFF         // Lower 16 Bits of 32 Bit DMT Window Interval (Lower 16 bits of 32 bit DMT window interval (0-0xFFFF))

// FDMTINTVH
#pragma config DMTIVTH = 0xFFFF         // Upper 16 Bits of 32 Bit DMT Window Interval (Upper 16 bits of 32 bit DMT window interval (0-0xFFFF))

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF))

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF))

// FDMT
#pragma config DMTEN = DISABLE           // Dead Man Timer Enable Bit (Dead Man Timer is Enabled and cannot be disabled by software)

// FDEVOPT
#pragma config PWMLOCK = ON             // PWM Lock Enable Bit (Certain PWM registers may only be written after key sequence)
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pins Selection Bit (I2C1 mapped to SDA1/SCL1 pins)

// FALTREG
#pragma config CTXT1 = NONE             // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 1 (Not Assigned)
#pragma config CTXT2 = NONE             // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 2 (Not Assigned)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/*
 * 寄存器 FSEC 
    BWRP  引导段写保护位 1 = 用户程序存储区不被写保护 0 = 用户程序存储区被写保护
    BSS<1:0>  引导段代码闪存保护级别位 11 = 无保护（BWRP写保护除外）10 = 标准安全性 0x = 高安全性
    BSEN  引导段控制位 1 = 无引导段 0 = 引导段大小由BSLIM<12:0>决定
    GWRP  通用段写保护位 1 = 用户程序存储区不被写保护 0 = 用户程序存储区被写保护
    GSS<1:0>  通用段代码闪存保护级别位 11 = 无保护（GWRP写保护除外）10 = 标准安全性 0x = 高安全性
    CWRP  配置段写保护位 1 = 配置段未被写保护 0 = 配置段被写保护
    CSS<2:0> 配置段代码闪存保护级别位  111 = 无保护（CWRP写保护除外）110 = 标准安全性 
                                       10x = 增强型安全性 0xx = 高安全性
    AIVTDIS FSEC 备用中断向量表禁止位 1 = 禁止AIVT 0 = 使能AIVT
 * 寄存器 FBSLIM
    BSLIM<12:0> 引导段代码闪存页地址限制位
        包含第一个有效的通用段页的页地址。要编程的值为页地址的补码，这样编程额外的0只会增加引导段的大小。
        例如，0x1FFD = 2页或1024个指令字。
 * 寄存器FOSCSEL
    FNOSC<2:0> 初始振荡器源选择位
        111 = 带后分频器的内部快速RC（FRC）振荡器
        110 = 16分频内部快速RC（FRC）振荡器
        101 = LPRC振荡器
        100 = 保留
        011 = 带PLL的主振荡器（XT、HS和EC）
        010 = 主（XT、HS和EC）振荡器
        001 = 带PLL的内部快速RC（FRC）振荡器
        000 = FRC振荡器
    IESO 双速振荡器启动使能位
        1 = 使用FRC启动器件，然后自动切换到就绪的用户选择的振荡器源
        0 = 使用用户选择的振荡器源启动器件
 * FOSC
    POSCMD<1:0> 主振荡器模式选择位
        11 = 禁止主振荡器
        10 = HS晶振模式
        01 = XT晶振模式
        00 = EC（外部时钟）模式
    OSCIOFNC OSC2引脚功能位（XT和HS模式除外）1 = OSC2为时钟输出 0 = OSC2为通用数字I/O引脚
    IOL1WAY 外设引脚选择配置位 1 = 只允许一次重新配置 0 = 允许多次重新配置
    FCKSM<1:0> 时钟切换模式位
        1x = 禁止时钟切换，禁止故障保护时钟监视器
        01 = 使能时钟切换，禁止故障保护时钟监视器
        00 = 使能时钟切换，使能故障保护时钟监视器
    PLLKEN PLL锁定等待使能位 1 = 只有等待直到PLL锁定信号有效时，时钟才会切换为PLL源 0 = 时钟切换不会等待PLL锁定
 * 寄存器 FWDT
    WDTPS<3:0> 看门狗定时器后分频比位
        1111 = 1:32,768
        1110 = 1:16,384
        ...
        0001 = 1:2
        0000 = 1:1
    WDTPRE 看门狗定时器预分频比位 1 = 1:128 0 = 1:32
    FWDTEN<1:0> 看门狗定时器使能位
        11 =在硬件中使能WDT
        10 =通过SWDTEN位控制WDT
        01 =WDT仅在器件激活时使能，在休眠时禁止；禁止SWDTEN位
        00 =禁止WDT和SWDTEN位
    WINDIS 看门狗定时器窗口使能位 1 = 看门狗定时器处于非窗口模式 0 = 看门狗定时器处于窗口模式
    WDTWIN<1:0> 看门狗定时器窗口选择位
        11 = WDT窗口为WDT周期的25%
        10 = WDT窗口为WDT周期的37.5%
        01 = WDT窗口为WDT周期的50%
        00 = WDT窗口为WDT周期的75%
 * 寄存器 FPOR
    BOREN 欠压复位（BOR）检测使能位 1 = 使能BOR 0 = 禁止BOR
 * 寄存器 FICD
    ICS<1:0> ICD通信通道选择位
        11 = 通过PGEC1和PGED1进行通信
        10 = 通过PGEC2和PGED2进行通信
        01 = 通过PGEC3和PGED3进行通信
        00 = 保留，不要使用
 * DMTIVT<15:0> FDMTINTVL 用于配置DMT窗口间隔的32位位域的低16位
 * DMTIVT<31:16> FDMTINTVH 用于配置DMT窗口间隔的32位位域的高16位
 * DMTCNT<15:0> FDMTCNTL 用于配置DMT指令计数超时值的32位位域的低16位
 * DMTCNT<31:16> FDMCNTH 用于配置DMT指令计数超时值的32位位域的高16位
 * DMTEN FDMT 程序监控定时器事使能位
    1 = 使能程序监控定时器且无法用软件禁止
    0 = 禁止程序监控定时器且可用软件使能
 * 寄存器 FDEVOPT
    PWMLOCK PWM锁定使能位
        1 = 只有在密钥序列之后，才能对某些PWM寄存器进行写操作
        0 = 无需密钥序列即可对PWM寄存器进行写操作
    ALTI2C1 I2C1的备用I 2 C引脚位
        1 = I2C1被映射到SDA1/SCL1引脚
        0 = I2C1被映射到ASDA1/ASCL1引脚
 * CTXT1<2:0> FALTREG
    指定备用工作寄存器组1与中断优先级（IPL）关联的位
        111 = 未分配
        110 = 为备用寄存器组1分配IPL级别6
        101 = 为备用寄存器组1分配IPL级别5
        100 = 为备用寄存器组1分配IPL级别4
        011 = 为备用寄存器组1分配IPL级别3
        010 = 为备用寄存器组1分配IPL级别2
        001 = 为备用寄存器组1分配IPL级别1
        000 = 未分配
 * CTXT2<2:0> FALTREG
    指定备用工作寄存器组2与中断优先级（IPL）关联的位
        111 = 未分配
        110 = 为备用寄存器组2分配IPL级别6
        101 = 为备用寄存器组2分配IPL级别5
        100 = 为备用寄存器组2分配IPL级别4
        011 = 为备用寄存器组2分配IPL级别3
        010 = 为备用寄存器组2分配IPL级别2
        001 = 为备用寄存器组2分配IPL级别1
        000 = 未分配 */


//_FOSCSEL(FNOSC_FRC & IESO_OFF);
//_FOSC(POSCMD_XT & OSCIOFNC_OFF & FCKSM_CSECMD & PLLKEN_ON);
//
//_FWDT(WDTPOST_PS128 & WDTPRE_PR128 & FWDTEN_ON);
//_FPOR(BOREN0_ON);
//_FICD(ICS_PGD1);