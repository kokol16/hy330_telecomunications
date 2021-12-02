#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Lab2 3
# GNU Radio version: 3.8.1.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
import sip
from gnuradio import analog
from gnuradio import blocks
import numpy
from gnuradio import digital
from gnuradio import gr
from gnuradio.filter import firdes
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
import math
from gnuradio import qtgui

class lab2_3(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Lab2 3")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Lab2 3")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "lab2_3")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 1e6
        self.noise = noise = 0.0
        self.mod_order = mod_order = 3
        self.constellation_qpsk_norm = constellation_qpsk_norm = [0.70710678118 * -1 - 0.70710678118 * 1j, 0.70710678118 * -1 + 0.70710678118 * 1j, 0.70710678118 * 1 - 0.70710678118 * 1j, 0.70710678118 * 1 + 0.70710678118 * 1j]
        self.constellation_qpsk = constellation_qpsk = [1+1j, 1-1j, -1+1j, -1-1j]
        self.constellation_qam_64_norm = constellation_qam_64_norm = [0.15430335 * -7 - 0.15430335 * 7j, 0.15430335 * -7 - 0.15430335 * 5j, 0.15430335 * -7 - 0.15430335 * 3j, 0.15430335 * -7 - 0.15430335 * 1j, 0.15430335 * -7 + 0.15430335 * 1j, 0.15430335 * -7 + 0.15430335 * 3j, 0.15430335 * -7 + 0.15430335 * 5j, 0.15430335 * -7 + 0.15430335 * 7j, 0.15430335 * -5 - 0.15430335 * 7j, 0.15430335 * -5 - 0.15430335 * 5j, 0.15430335 * -5 - 0.15430335 * 3j, 0.15430335 * -5 - 0.15430335 * 1j, 0.15430335 * -5 + 0.15430335 * 1j, 0.15430335 * -5 +
        0.15430335 * 3j, 0.15430335 * -5 + 0.15430335 * 5j, 0.15430335 * -5 + 0.15430335 * 7j, 0.15430335 * -3 - 0.15430335 * 7j, 0.15430335 * -3 - 0.15430335 * 5j, 0.15430335 * -3 - 0.15430335 * 3j, 0.15430335 * -3 - 0.15430335 * 1j, 0.15430335 * -3 + 0.15430335 * 1j, 0.15430335 * -3 + 0.15430335 * 3j, 0.15430335 * -3 + 0.15430335 * 5j, 0.15430335 * -3 + 0.15430335 * 7j, 0.15430335 * -1 - 0.15430335 * 7j, 0.15430335 * -1 - 0.15430335 * 5j, 0.15430335 * -1 - 0.15430335 * 3j, 0.15430335 * -1 - 0.15430335 * 1j, 0.15430335 * -1 + 0.15430335 * 1j, 0.15430335 * -1 + 0.15430335 * 3j, 0.15430335 * -1 + 0.15430335 * 5j, 0.15430335 * -1 + 0.15430335 * 7j, 0.15430335 * 1 - 0.15430335 * 7j, 0.15430335 * 1 - 0.15430335 *
        5j, 0.15430335 * 1 - 0.15430335 * 3j, 0.15430335 * 1 - 0.15430335 * 1j, 0.15430335 * 1 + 0.15430335 * 1j, 0.15430335 * 1 + 0.15430335 * 3j, 0.15430335 * 1 + 0.15430335 * 5j, 0.15430335 * 1 + 0.15430335 * 7j, 0.15430335 * 3 - 0.15430335 * 7j, 0.15430335 * 3 - 0.15430335 * 5j, 0.15430335 * 3 - 0.15430335 * 3j, 0.15430335 * 3 - 0.15430335 * 1j, 0.15430335 * 3 + 0.15430335 * 1j, 0.15430335 * 3 + 0.15430335 * 3j, 0.15430335 * 3 + 0.15430335 * 5j, 0.15430335 * 3 + 0.15430335
        * 7j, 0.15430335 * 5 - 0.15430335 * 7j, 0.15430335 * 5 - 0.15430335 * 5j, 0.15430335 * 5 - 0.15430335 * 3j, 0.15430335 * 5 - 0.15430335 * 1j, 0.15430335 * 5 + 0.15430335 * 1j, 0.15430335 * 5 + 0.15430335 * 3j, 0.15430335 * 5 + 0.15430335 * 5j, 0.15430335 * 5 + 0.15430335 * 7j, 0.15430335 * 7 - 0.15430335 * 7j, 0.15430335 * 7 - 0.15430335 * 5j, 0.15430335 * 7 - 0.15430335 * 3j, 0.15430335 * 7 - 0.15430335 * 1j, 0.15430335 * 7 + 0.15430335 * 1j, 0.15430335 * 7 + 0.15430335 * 3j, 0.15430335 * 7 + 0.15430335 * 5j, 0.15430335 * 7 + 0.15430335 * 7j]
        self.constellation_qam_64 = constellation_qam_64 = [-7 - 7j, -7 - 5j, -7 - 3j, -7 - 1j, -7 + 1j, -7 + 3j, -7 + 5j, -7 + 7j, -5 - 7j, -5 - 5j, -5 - 3j, -5 - 1j, -5 + 1j, -5 + 3j, -5 + 5j, -5 + 7j, -3 - 7j, -3 - 5j, -3 - 3j, -3 - 1j, -3 + 1j, -3 + 3j, -3 + 5j, -3 + 7j, -1 - 7j, -1 - 5j, -1 - 3j, -1 - 1j, -1 + 1j, -1 + 3j, -1 + 5j, -1 + 7j, 1 - 7j, 1 - 5j, 1 - 3j, 1 - 1j, 1 + 1j, 1 + 3j, 1 + 5j, 1 + 7j, 3 - 7j, 3 - 5j, 3 - 3j, 3 - 1j, 3 + 1j, 3 + 3j, 3 + 5j, 3 + 7j, 5 - 7j, 5 - 5j, 5 - 3j, 5 - 1j, 5 + 1j, 5 + 3j, 5 + 5j, 5 + 7j, 7 - 7j, 7 - 5j, 7 - 3j, 7 - 1j, 7 + 1j, 7 + 3j, 7 + 5j, 7 + 7j]
        self.constellation_qam_16_norm = constellation_qam_16_norm = [0.316227766 * -3 - 0.316227766 * 3j, 0.316227766 * -3 - 0.316227766 * 1j, 0.316227766 * -3 + 0.316227766 * 1j, 0.316227766 * -3 + 0.316227766 * 3j, 0.316227766 * -1 - 0.316227766 * 3j, 0.316227766 * -1 - 0.316227766 * 1j, 0.316227766 * -1 + 0.316227766 * 1j, 0.316227766 * -1 + 0.316227766 * 3j, 0.316227766 * 1 - 0.316227766 * 3j, 0.316227766 * 1 - 0.316227766 * 1j, 0.316227766 * 1 + 0.316227766 * 1j, 0.316227766 * 1 + 0.316227766 * 3j, 0.316227766 * 3 - 0.316227766 * 3j, 0.316227766 * 3 - 0.316227766 * 1j, 0.316227766 * 3 + 0.316227766 * 1j, 0.316227766 * 3 + 0.316227766 * 3j]
        self.constellation_qam_16 = constellation_qam_16 = [-3+3j,-1+3j,-3+1j,-1+1j,3+3j,1+3j,3+1j,1+1j,1-1j,3-1j,1-3j,3-3j,-1-1j,-3-1j,-1-3j,-3-3j]
        self.constellation_bpsk = constellation_bpsk = [-1+0j, +1+0j]
        self.constellation_8psk = constellation_8psk = [+1+0j,0.707 + 0.707j,0+1j,-0.707 + 0.707j,-1+0j,-0.707 - 0.707j,0-1j,0.707 - 0.707j]
        self.cfo = cfo = 0.0

        ##################################################
        # Blocks
        ##################################################
        self._noise_range = Range(0, 1, 0.01, 0.0, 200)
        self._noise_win = RangeWidget(self._noise_range, self.set_noise, 'Noise Amplitude', "counter_slider", float)
        self.top_grid_layout.addWidget(self._noise_win)
        self._cfo_range = Range(0, 100e3, 10, 0.0, 200)
        self._cfo_win = RangeWidget(self._cfo_range, self.set_cfo, 'Carrier Frequency Offset (Hz)', "counter_slider", float)
        self.top_grid_layout.addWidget(self._cfo_win)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            1024, #size
            "", #name
            1 #number of inputs
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(True)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bc(constellation_8psk, 1)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_packed_to_unpacked_xx_0 = blocks.packed_to_unpacked_bb(mod_order, gr.GR_MSB_FIRST)
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_sig_source_x_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, cfo, 1, 0, 0)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, 255, 1000))), True)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, noise, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_packed_to_unpacked_xx_0, 0))
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_multiply_xx_0, 1))
        self.connect((self.blocks_add_xx_0, 0), (self.blocks_multiply_xx_0, 0))
        self.connect((self.blocks_multiply_xx_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_packed_to_unpacked_xx_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.blocks_add_xx_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "lab2_3")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_noise(self):
        return self.noise

    def set_noise(self, noise):
        self.noise = noise
        self.analog_noise_source_x_0.set_amplitude(self.noise)

    def get_mod_order(self):
        return self.mod_order

    def set_mod_order(self, mod_order):
        self.mod_order = mod_order

    def get_constellation_qpsk_norm(self):
        return self.constellation_qpsk_norm

    def set_constellation_qpsk_norm(self, constellation_qpsk_norm):
        self.constellation_qpsk_norm = constellation_qpsk_norm

    def get_constellation_qpsk(self):
        return self.constellation_qpsk

    def set_constellation_qpsk(self, constellation_qpsk):
        self.constellation_qpsk = constellation_qpsk

    def get_constellation_qam_64_norm(self):
        return self.constellation_qam_64_norm

    def set_constellation_qam_64_norm(self, constellation_qam_64_norm):
        self.constellation_qam_64_norm = constellation_qam_64_norm

    def get_constellation_qam_64(self):
        return self.constellation_qam_64

    def set_constellation_qam_64(self, constellation_qam_64):
        self.constellation_qam_64 = constellation_qam_64

    def get_constellation_qam_16_norm(self):
        return self.constellation_qam_16_norm

    def set_constellation_qam_16_norm(self, constellation_qam_16_norm):
        self.constellation_qam_16_norm = constellation_qam_16_norm

    def get_constellation_qam_16(self):
        return self.constellation_qam_16

    def set_constellation_qam_16(self, constellation_qam_16):
        self.constellation_qam_16 = constellation_qam_16

    def get_constellation_bpsk(self):
        return self.constellation_bpsk

    def set_constellation_bpsk(self, constellation_bpsk):
        self.constellation_bpsk = constellation_bpsk

    def get_constellation_8psk(self):
        return self.constellation_8psk

    def set_constellation_8psk(self, constellation_8psk):
        self.constellation_8psk = constellation_8psk
        self.digital_chunks_to_symbols_xx_0.set_symbol_table(self.constellation_8psk)

    def get_cfo(self):
        return self.cfo

    def set_cfo(self, cfo):
        self.cfo = cfo
        self.analog_sig_source_x_0.set_frequency(self.cfo)



def main(top_block_cls=lab2_3, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
