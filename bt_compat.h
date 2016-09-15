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

#ifndef hci_recv_diag
/* Receive diagnostic message from HCI drivers */
static inline int hci_recv_diag(struct hci_dev *hdev, struct sk_buff *skb)
{
	/* Mark as diagnostic packet */
	hci_skb_pkt_type(skb) = HCI_DIAG_PKT;

	/* Time stamp */
	__net_timestamp(skb);

	skb_queue_tail(&hdev->rx_q, skb);
	queue_work(hdev->workqueue, &hdev->rx_work);

	return 0;
}
#endif

