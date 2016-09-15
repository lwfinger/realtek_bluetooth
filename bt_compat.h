/* header file that contains all adjustments needed to build on older kernels */

#ifndef HCI_PRIMARY
#define HCI_PRIMARY 0
#endif

#ifndef hci_skb_pkt_type
#define hci_skb_pkt_type(skb) bt_cb((skb))->pkt_type
#endif

#ifndef hci_skb_expect
#define hci_skb_expect(skb) bt_cb((skb))->expect
#endif

