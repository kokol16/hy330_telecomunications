# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.1
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _constellation_mapping_swig
else:
    import _constellation_mapping_swig

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)



def high_res_timer_now() -> "gr::high_res_timer_type":
    r"""high_res_timer_now() -> gr::high_res_timer_type"""
    return _constellation_mapping_swig.high_res_timer_now()

def high_res_timer_now_perfmon() -> "gr::high_res_timer_type":
    r"""high_res_timer_now_perfmon() -> gr::high_res_timer_type"""
    return _constellation_mapping_swig.high_res_timer_now_perfmon()

def high_res_timer_tps() -> "gr::high_res_timer_type":
    r"""high_res_timer_tps() -> gr::high_res_timer_type"""
    return _constellation_mapping_swig.high_res_timer_tps()

def high_res_timer_epoch() -> "gr::high_res_timer_type":
    r"""high_res_timer_epoch() -> gr::high_res_timer_type"""
    return _constellation_mapping_swig.high_res_timer_epoch()
class constellation_mapping(object):
    r"""
    <+description of block+>

    Constructor Specific Documentation:

    Return a shared_ptr to a new instance of constellation_mapping::constellation_mapping.

    To avoid accidental use of raw pointers, constellation_mapping::constellation_mapping's constructor is in a private implementation class. constellation_mapping::constellation_mapping::make is the public interface for creating new instances.
    """

    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined")
    __repr__ = _swig_repr

    @staticmethod
    def make() -> "gr::constellation_mapping::constellation_mapping::sptr":
        r"""
        make() -> constellation_mapping_sptr
        <+description of block+>

        Constructor Specific Documentation:

        Return a shared_ptr to a new instance of constellation_mapping::constellation_mapping.

        To avoid accidental use of raw pointers, constellation_mapping::constellation_mapping's constructor is in a private implementation class. constellation_mapping::constellation_mapping::make is the public interface for creating new instances.
        """
        return _constellation_mapping_swig.constellation_mapping_make()
    __swig_destroy__ = _constellation_mapping_swig.delete_constellation_mapping

# Register constellation_mapping in _constellation_mapping_swig:
_constellation_mapping_swig.constellation_mapping_swigregister(constellation_mapping)

def constellation_mapping_make() -> "gr::constellation_mapping::constellation_mapping::sptr":
    r"""
    constellation_mapping_make() -> constellation_mapping_sptr
    <+description of block+>

    Constructor Specific Documentation:

    Return a shared_ptr to a new instance of constellation_mapping::constellation_mapping.

    To avoid accidental use of raw pointers, constellation_mapping::constellation_mapping's constructor is in a private implementation class. constellation_mapping::constellation_mapping::make is the public interface for creating new instances.
    """
    return _constellation_mapping_swig.constellation_mapping_make()

class constellation_mapping_sptr(object):
    r"""Proxy of C++ boost::shared_ptr< gr::constellation_mapping::constellation_mapping > class."""

    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        r"""
        __init__(constellation_mapping_sptr self) -> constellation_mapping_sptr
        __init__(constellation_mapping_sptr self, constellation_mapping p) -> constellation_mapping_sptr
        """
        _constellation_mapping_swig.constellation_mapping_sptr_swiginit(self, _constellation_mapping_swig.new_constellation_mapping_sptr(*args))

    def __deref__(self) -> "gr::constellation_mapping::constellation_mapping *":
        r"""__deref__(constellation_mapping_sptr self) -> constellation_mapping"""
        return _constellation_mapping_swig.constellation_mapping_sptr___deref__(self)
    __swig_destroy__ = _constellation_mapping_swig.delete_constellation_mapping_sptr

    def make(self) -> "gr::constellation_mapping::constellation_mapping::sptr":
        r"""
        make(constellation_mapping_sptr self) -> constellation_mapping_sptr
        <+description of block+>

        Constructor Specific Documentation:

        Return a shared_ptr to a new instance of constellation_mapping::constellation_mapping.

        To avoid accidental use of raw pointers, constellation_mapping::constellation_mapping's constructor is in a private implementation class. constellation_mapping::constellation_mapping::make is the public interface for creating new instances.
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_make(self)

    def history(self) -> "unsigned int":
        r"""history(constellation_mapping_sptr self) -> unsigned int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_history(self)

    def declare_sample_delay(self, *args) -> "void":
        r"""
        declare_sample_delay(constellation_mapping_sptr self, int which, int delay)
        declare_sample_delay(constellation_mapping_sptr self, unsigned int delay)
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_declare_sample_delay(self, *args)

    def sample_delay(self, which: "int") -> "unsigned int":
        r"""sample_delay(constellation_mapping_sptr self, int which) -> unsigned int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_sample_delay(self, which)

    def set_output_multiple(self, multiple: "int") -> "void":
        r"""set_output_multiple(constellation_mapping_sptr self, int multiple)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_output_multiple(self, multiple)

    def output_multiple(self) -> "int":
        r"""output_multiple(constellation_mapping_sptr self) -> int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_output_multiple(self)

    def relative_rate(self) -> "double":
        r"""relative_rate(constellation_mapping_sptr self) -> double"""
        return _constellation_mapping_swig.constellation_mapping_sptr_relative_rate(self)

    def relative_rate_i(self) -> "uint64_t":
        r"""relative_rate_i(constellation_mapping_sptr self) -> uint64_t"""
        return _constellation_mapping_swig.constellation_mapping_sptr_relative_rate_i(self)

    def relative_rate_d(self) -> "uint64_t":
        r"""relative_rate_d(constellation_mapping_sptr self) -> uint64_t"""
        return _constellation_mapping_swig.constellation_mapping_sptr_relative_rate_d(self)

    def start(self) -> "bool":
        r"""start(constellation_mapping_sptr self) -> bool"""
        return _constellation_mapping_swig.constellation_mapping_sptr_start(self)

    def stop(self) -> "bool":
        r"""stop(constellation_mapping_sptr self) -> bool"""
        return _constellation_mapping_swig.constellation_mapping_sptr_stop(self)

    def nitems_read(self, which_input: "unsigned int") -> "uint64_t":
        r"""nitems_read(constellation_mapping_sptr self, unsigned int which_input) -> uint64_t"""
        return _constellation_mapping_swig.constellation_mapping_sptr_nitems_read(self, which_input)

    def nitems_written(self, which_output: "unsigned int") -> "uint64_t":
        r"""nitems_written(constellation_mapping_sptr self, unsigned int which_output) -> uint64_t"""
        return _constellation_mapping_swig.constellation_mapping_sptr_nitems_written(self, which_output)

    def set_log_level(self, level: "std::string") -> "void":
        r"""set_log_level(constellation_mapping_sptr self, std::string level)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_log_level(self, level)

    def log_level(self) -> "std::string":
        r"""log_level(constellation_mapping_sptr self) -> std::string"""
        return _constellation_mapping_swig.constellation_mapping_sptr_log_level(self)

    def max_noutput_items(self) -> "int":
        r"""max_noutput_items(constellation_mapping_sptr self) -> int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_max_noutput_items(self)

    def set_max_noutput_items(self, m: "int") -> "void":
        r"""set_max_noutput_items(constellation_mapping_sptr self, int m)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_max_noutput_items(self, m)

    def unset_max_noutput_items(self) -> "void":
        r"""unset_max_noutput_items(constellation_mapping_sptr self)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_unset_max_noutput_items(self)

    def is_set_max_noutput_items(self) -> "bool":
        r"""is_set_max_noutput_items(constellation_mapping_sptr self) -> bool"""
        return _constellation_mapping_swig.constellation_mapping_sptr_is_set_max_noutput_items(self)

    def set_min_noutput_items(self, m: "int") -> "void":
        r"""set_min_noutput_items(constellation_mapping_sptr self, int m)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_min_noutput_items(self, m)

    def min_noutput_items(self) -> "int":
        r"""min_noutput_items(constellation_mapping_sptr self) -> int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_min_noutput_items(self)

    def max_output_buffer(self, i: "int") -> "long":
        r"""max_output_buffer(constellation_mapping_sptr self, int i) -> long"""
        return _constellation_mapping_swig.constellation_mapping_sptr_max_output_buffer(self, i)

    def set_max_output_buffer(self, *args) -> "void":
        r"""
        set_max_output_buffer(constellation_mapping_sptr self, long max_output_buffer)
        set_max_output_buffer(constellation_mapping_sptr self, int port, long max_output_buffer)
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_set_max_output_buffer(self, *args)

    def min_output_buffer(self, i: "int") -> "long":
        r"""min_output_buffer(constellation_mapping_sptr self, int i) -> long"""
        return _constellation_mapping_swig.constellation_mapping_sptr_min_output_buffer(self, i)

    def set_min_output_buffer(self, *args) -> "void":
        r"""
        set_min_output_buffer(constellation_mapping_sptr self, long min_output_buffer)
        set_min_output_buffer(constellation_mapping_sptr self, int port, long min_output_buffer)
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_set_min_output_buffer(self, *args)

    def pc_noutput_items(self) -> "float":
        r"""pc_noutput_items(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_noutput_items(self)

    def pc_noutput_items_avg(self) -> "float":
        r"""pc_noutput_items_avg(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_noutput_items_avg(self)

    def pc_noutput_items_var(self) -> "float":
        r"""pc_noutput_items_var(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_noutput_items_var(self)

    def pc_nproduced(self) -> "float":
        r"""pc_nproduced(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_nproduced(self)

    def pc_nproduced_avg(self) -> "float":
        r"""pc_nproduced_avg(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_nproduced_avg(self)

    def pc_nproduced_var(self) -> "float":
        r"""pc_nproduced_var(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_nproduced_var(self)

    def pc_input_buffers_full(self, *args) -> "std::vector< float,std::allocator< float > >":
        r"""
        pc_input_buffers_full(constellation_mapping_sptr self, int which) -> float
        pc_input_buffers_full(constellation_mapping_sptr self) -> pmt_vector_float
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_input_buffers_full(self, *args)

    def pc_input_buffers_full_avg(self, *args) -> "std::vector< float,std::allocator< float > >":
        r"""
        pc_input_buffers_full_avg(constellation_mapping_sptr self, int which) -> float
        pc_input_buffers_full_avg(constellation_mapping_sptr self) -> pmt_vector_float
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_input_buffers_full_avg(self, *args)

    def pc_input_buffers_full_var(self, *args) -> "std::vector< float,std::allocator< float > >":
        r"""
        pc_input_buffers_full_var(constellation_mapping_sptr self, int which) -> float
        pc_input_buffers_full_var(constellation_mapping_sptr self) -> pmt_vector_float
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_input_buffers_full_var(self, *args)

    def pc_output_buffers_full(self, *args) -> "std::vector< float,std::allocator< float > >":
        r"""
        pc_output_buffers_full(constellation_mapping_sptr self, int which) -> float
        pc_output_buffers_full(constellation_mapping_sptr self) -> pmt_vector_float
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_output_buffers_full(self, *args)

    def pc_output_buffers_full_avg(self, *args) -> "std::vector< float,std::allocator< float > >":
        r"""
        pc_output_buffers_full_avg(constellation_mapping_sptr self, int which) -> float
        pc_output_buffers_full_avg(constellation_mapping_sptr self) -> pmt_vector_float
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_output_buffers_full_avg(self, *args)

    def pc_output_buffers_full_var(self, *args) -> "std::vector< float,std::allocator< float > >":
        r"""
        pc_output_buffers_full_var(constellation_mapping_sptr self, int which) -> float
        pc_output_buffers_full_var(constellation_mapping_sptr self) -> pmt_vector_float
        """
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_output_buffers_full_var(self, *args)

    def pc_work_time(self) -> "float":
        r"""pc_work_time(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_work_time(self)

    def pc_work_time_avg(self) -> "float":
        r"""pc_work_time_avg(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_work_time_avg(self)

    def pc_work_time_var(self) -> "float":
        r"""pc_work_time_var(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_work_time_var(self)

    def pc_work_time_total(self) -> "float":
        r"""pc_work_time_total(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_work_time_total(self)

    def pc_throughput_avg(self) -> "float":
        r"""pc_throughput_avg(constellation_mapping_sptr self) -> float"""
        return _constellation_mapping_swig.constellation_mapping_sptr_pc_throughput_avg(self)

    def set_processor_affinity(self, mask: "std::vector< int,std::allocator< int > > const &") -> "void":
        r"""set_processor_affinity(constellation_mapping_sptr self, std::vector< int,std::allocator< int > > const & mask)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_processor_affinity(self, mask)

    def unset_processor_affinity(self) -> "void":
        r"""unset_processor_affinity(constellation_mapping_sptr self)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_unset_processor_affinity(self)

    def processor_affinity(self) -> "std::vector< int,std::allocator< int > >":
        r"""processor_affinity(constellation_mapping_sptr self) -> std::vector< int,std::allocator< int > >"""
        return _constellation_mapping_swig.constellation_mapping_sptr_processor_affinity(self)

    def active_thread_priority(self) -> "int":
        r"""active_thread_priority(constellation_mapping_sptr self) -> int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_active_thread_priority(self)

    def thread_priority(self) -> "int":
        r"""thread_priority(constellation_mapping_sptr self) -> int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_thread_priority(self)

    def set_thread_priority(self, priority: "int") -> "int":
        r"""set_thread_priority(constellation_mapping_sptr self, int priority) -> int"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_thread_priority(self, priority)

    def name(self) -> "std::string":
        r"""name(constellation_mapping_sptr self) -> std::string"""
        return _constellation_mapping_swig.constellation_mapping_sptr_name(self)

    def symbol_name(self) -> "std::string":
        r"""symbol_name(constellation_mapping_sptr self) -> std::string"""
        return _constellation_mapping_swig.constellation_mapping_sptr_symbol_name(self)

    def input_signature(self) -> "gr::io_signature::sptr":
        r"""input_signature(constellation_mapping_sptr self) -> io_signature_sptr"""
        return _constellation_mapping_swig.constellation_mapping_sptr_input_signature(self)

    def output_signature(self) -> "gr::io_signature::sptr":
        r"""output_signature(constellation_mapping_sptr self) -> io_signature_sptr"""
        return _constellation_mapping_swig.constellation_mapping_sptr_output_signature(self)

    def unique_id(self) -> "long":
        r"""unique_id(constellation_mapping_sptr self) -> long"""
        return _constellation_mapping_swig.constellation_mapping_sptr_unique_id(self)

    def to_basic_block(self) -> "gr::basic_block_sptr":
        r"""to_basic_block(constellation_mapping_sptr self) -> basic_block_sptr"""
        return _constellation_mapping_swig.constellation_mapping_sptr_to_basic_block(self)

    def check_topology(self, ninputs: "int", noutputs: "int") -> "bool":
        r"""check_topology(constellation_mapping_sptr self, int ninputs, int noutputs) -> bool"""
        return _constellation_mapping_swig.constellation_mapping_sptr_check_topology(self, ninputs, noutputs)

    def alias(self) -> "std::string":
        r"""alias(constellation_mapping_sptr self) -> std::string"""
        return _constellation_mapping_swig.constellation_mapping_sptr_alias(self)

    def set_block_alias(self, name: "std::string") -> "void":
        r"""set_block_alias(constellation_mapping_sptr self, std::string name)"""
        return _constellation_mapping_swig.constellation_mapping_sptr_set_block_alias(self, name)

    def _post(self, which_port: "swig_pmt_ptr", msg: "swig_pmt_ptr") -> "void":
        r"""_post(constellation_mapping_sptr self, swig_pmt_ptr which_port, swig_pmt_ptr msg)"""
        return _constellation_mapping_swig.constellation_mapping_sptr__post(self, which_port, msg)

    def message_ports_in(self) -> "pmt::pmt_t":
        r"""message_ports_in(constellation_mapping_sptr self) -> swig_pmt_ptr"""
        return _constellation_mapping_swig.constellation_mapping_sptr_message_ports_in(self)

    def message_ports_out(self) -> "pmt::pmt_t":
        r"""message_ports_out(constellation_mapping_sptr self) -> swig_pmt_ptr"""
        return _constellation_mapping_swig.constellation_mapping_sptr_message_ports_out(self)

    def message_subscribers(self, which_port: "swig_pmt_ptr") -> "pmt::pmt_t":
        r"""message_subscribers(constellation_mapping_sptr self, swig_pmt_ptr which_port) -> swig_pmt_ptr"""
        return _constellation_mapping_swig.constellation_mapping_sptr_message_subscribers(self, which_port)

# Register constellation_mapping_sptr in _constellation_mapping_swig:
_constellation_mapping_swig.constellation_mapping_sptr_swigregister(constellation_mapping_sptr)


constellation_mapping_sptr.__repr__ = lambda self: "<gr_block %s (%d)>" % (self.name(), self.unique_id())
constellation_mapping = constellation_mapping.make;


