/* header file that contains all adjustments needed to build on older kernels */

#ifndef HCI_PRIMARY
#define HCI_PRIMARY 0
#endif

#ifndef HCI_DIAG_PKT
#define HCI_DIAG_PKT                0xf0
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

#ifndef HCI_QUIRK_NON_PERSISTENT_DIAG
/* HCI device quirks */
enum {
        /* When this quirk is set, the HCI Reset command is send when
         * closing the transport instead of when opening it.
         *
         * This quirk must be set before hci_register_dev is called.
         */
        HCI_QUIRK_RESET_ON_CLOSE,

        /* When this quirk is set, the device is turned into a raw-only
         * device and it will stay in unconfigured state.
         *
         * This quirk must be set before hci_register_dev is called.
         */
        HCI_QUIRK_RAW_DEVICE,

        /* When this quirk is set, the buffer sizes reported by
         * HCI Read Buffer Size command are corrected if invalid.
         *
         * This quirk must be set before hci_register_dev is called.
         */
        HCI_QUIRK_FIXUP_BUFFER_SIZE,

        /* When this quirk is set, then a controller that does not
         * indicate support for Inquiry Result with RSSI is assumed to
         * support it anyway. Some early Bluetooth 1.2 controllers had
         * wrongly configured local features that will require forcing
         * them to enable this mode. Getting RSSI information with the
         * inquiry responses is preferred since it allows for a better
         * user expierence.
         *
         * This quirk must be set before hci_register_dev is called.
         */
        HCI_QUIRK_FIXUP_INQUIRY_MODE,

        /* When this quirk is set, then the HCI Read Local Supported
         * Commands command is not supported. In general Bluetooth 1.2
         * and later controllers should support this command. However
         * some controllers indicate Bluetooth 1.2 support, but do
         * not support this command.
         *
         * This quirk must be set before hci_register_dev is called.
         */
        HCI_QUIRK_BROKEN_LOCAL_COMMANDS,

        /* When this quirk is set, then no stored link key handling
         * is performed. This is mainly due to the fact that the
         * HCI Delete Stored Link Key command is advertised, but
         * not supported.
         *
         * This quirk must be set before hci_register_dev is called.
         */
        HCI_QUIRK_BROKEN_STORED_LINK_KEY,

        /* When this quirk is set, an external configuration step
         * is required and will be indicated with the controller
         * configuation.
         *
         * This quirk can be set before hci_register_dev is called or
         * during the hdev->setup vendor callback.
         */
        HCI_QUIRK_EXTERNAL_CONFIG,

        /* When this quirk is set, the public Bluetooth address
         * initially reported by HCI Read BD Address command
         * is considered invalid. Controller configuration is
         * required before this device can be used.
         *
         * This quirk can be set before hci_register_dev is called or
         * during the hdev->setup vendor callback.
         */
        HCI_QUIRK_INVALID_BDADDR,

        /* When this quirk is set, the duplicate filtering during
         * scanning is based on Bluetooth devices addresses. To allow
         * RSSI based updates, restart scanning if needed.
         *
         * This quirk can be set before hci_register_dev is called or
         * during the hdev->setup vendor callback.
         */
        HCI_QUIRK_STRICT_DUPLICATE_FILTER,

        /* When this quirk is set, LE scan and BR/EDR inquiry is done
         * simultaneously, otherwise it's interleaved.
         *
         * This quirk can be set before hci_register_dev is called or
         * during the hdev->setup vendor callback.
         */
        HCI_QUIRK_SIMULTANEOUS_DISCOVERY,

        /* When this quirk is set, the enabling of diagnostic mode is
         * not persistent over HCI Reset. Every time the controller
         * is brought up it needs to be reprogrammed.
         *
         * This quirk can be set before hci_register_dev is called or
         * during the hdev->setup vendor callback.
         */
        HCI_QUIRK_NON_PERSISTENT_DIAG,
};
#endif

