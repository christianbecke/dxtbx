#include <boost/python.hpp>
#include <boost/python/def.hpp>
#include <scitbx/array_family/shared.h>
#include <scitbx/array_family/flex_types.h>
#include <vector>
#include <dxtbx/imageset.h>
#include <dxtbx/error.h>

namespace dxtbx { namespace boost_python {


  template<typename T>
  void external_lookup_item_wrapper(const char *name) {
    using namespace boost::python;

    class_< ExternalLookupItem<T> >(name)
      .add_property("filename",
          &ExternalLookupItem<T>::get_filename,
          &ExternalLookupItem<T>::set_filename)
      .add_property("data",
          &ExternalLookupItem<T>::get_data,
          &ExternalLookupItem<T>::set_data)
      ;

  }

  void export_imageset() {
    using namespace boost::python;

    external_lookup_item_wrapper<double>("ExternalLookupItemDouble");
    external_lookup_item_wrapper<bool>("ExternalLookupItemBool");

     class_<ExternalLookup>("ExternalLookup")
      .add_property("mask",
          make_function(
            &ExternalLookup::mask,
            return_internal_reference<>()))
      .add_property("gain",
          make_function(
            &ExternalLookup::gain,
            return_internal_reference<>()))
      .add_property("pedestal",
          make_function(
            &ExternalLookup::pedestal,
            return_internal_reference<>()))
      ;

    class_<ImageSetData>("ImageSetDataWrapper", no_init)
      .def(init<
          boost::python::object,
          boost::python::object>())
      .def("get_data", &ImageSetData::get_data)
      .def("get_mask", &ImageSetData::get_mask)
      .def("has_single_file_reader", &ImageSetData::has_single_file_reader)
      .def("get_path", &ImageSetData::get_path)
      .def("get_master_path", &ImageSetData::get_master_path)
      .def("get_image_identifier", &ImageSetData::get_image_identifier)
      .def("get_property", &ImageSetData::get_property)
      .def("set_property", &ImageSetData::set_property)
      .def("get_beam", &ImageSetData::get_beam)
      .def("get_detector", &ImageSetData::get_detector)
      .def("get_goniometer", &ImageSetData::get_goniometer)
      .def("get_scan", &ImageSetData::get_scan)
      .def("set_beam", &ImageSetData::set_beam)
      .def("set_detector", &ImageSetData::set_detector)
      .def("set_goniometer", &ImageSetData::set_goniometer)
      .def("set_scan", &ImageSetData::set_scan)
      .add_property("external_lookup",
          make_function(
            &ImageSet::external_lookup,
            return_internal_reference<>()))
      ;

    class_<ImageSet>("ImageSet", no_init)
      .def(init<
          const ImageSetData &
          >())
      .def(init<
          const ImageSetData &,
          const scitbx::af::const_ref<std::size_t> &
          >())
      .def("data", &ImageSet::data)
      .def("indices", &ImageSet::indices)
      .def("size", &ImageSet::size)
      .def("get_raw_data", &ImageSet::get_raw_data)
      .def("get_corrected_data", &ImageSet::get_corrected_data)
      .def("get_gain", &ImageSet::get_gain)
      .def("get_pedestal", &ImageSet::get_pedestal)
      .def("get_mask", &ImageSet::get_mask)
      .def("get_property", &ImageSet::get_property)
      .def("set_property", &ImageSet::set_property)
      .def("get_beam", &ImageSet::get_beam_for_image)
      .def("get_detector", &ImageSet::get_detector_for_image)
      .def("get_goniometer", &ImageSet::get_goniometer_for_image)
      .def("get_scan", &ImageSet::get_scan_for_image)
      .def("set_beam", &ImageSet::set_beam_for_image)
      .def("set_detector", &ImageSet::set_detector_for_image)
      .def("set_goniometer", &ImageSet::set_goniometer_for_image)
      .def("set_scan", &ImageSet::set_scan_for_image)
      .def("get_path", &ImageSet::get_path)
      .def("get_image_identifier", &ImageSet::get_image_identifier)
      .def("as_imageset", &ImageSet::as_imageset)
      .def("complete_set", &ImageSet::complete_set)
      .def("partial_set", &ImageSet::partial_set)
      .def("__eq__", &ImageSet::operator==)
      .def("__ne__", &ImageSet::operator!=)
      .add_property("external_lookup",
          make_function(
            &ImageSet::external_lookup,
            return_internal_reference<>()))
      ;

    class_<ImageGrid, bases<ImageSet> >("ImageGrid", no_init)
      .def(init<
          const ImageSetData &,
          int2
          >())
      .def(init<
          const ImageSetData &,
          const scitbx::af::const_ref<std::size_t> &,
          int2
          >())
      .def("get_grid_size", &ImageGrid::get_grid_size)
      .def("from_imageset", &ImageGrid::from_imageset)
      ;

    class_<ImageSweep, bases<ImageSet> >("ImageSweep", no_init)
      .def(init<
          const ImageSetData &,
          const Beam &,
          const Detector &,
          const Goniometer &,
          const Scan &
          >())
      .def(init<
          const ImageSetData &,
          const scitbx::af::const_ref<std::size_t> &,
          const Beam &,
          const Detector &,
          const Goniometer &,
          const Scan &
          >())
      .def("get_beam", &ImageSweep::get_beam)
      .def("get_detector", &ImageSweep::get_detector)
      .def("get_goniometer", &ImageSweep::get_goniometer)
      .def("get_scan", &ImageSweep::get_scan)
      .def("set_beam", &ImageSweep::set_beam)
      .def("set_detector", &ImageSweep::set_detector)
      .def("set_goniometer", &ImageSweep::set_goniometer)
      .def("set_scan", &ImageSweep::set_scan)
      .def("get_array_range", &ImageSweep::get_array_range)
      .def("complete_set", &ImageSweep::complete_sweep)
      .def("partial_set", &ImageSweep::partial_sweep)
      ;
  }


  BOOST_PYTHON_MODULE(dxtbx_imageset_ext)
  {
    export_imageset();
  }

}} //namespace dxtbx::boost_python
