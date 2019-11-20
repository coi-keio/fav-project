/**
 * @author Takumi Moriya
 * @version 0.0.1
 */

THREE.FAVExporter = function () {};

THREE.FAVExporter.prototype = {

	constructor: THREE.FAVExporter,

  getIndex: function (x, y, z, dx, dy, dz) {
    return (dx * dy * z) + (dx * y) + x;
  },

  voxelsToArray: function (nonMergedVoxels, dimension, voxelSize) {
    var max_x = Number.MIN_SAFE_INTEGER;
    var max_y = Number.MIN_SAFE_INTEGER;
    var max_z = Number.MIN_SAFE_INTEGER;
    var min_x = Number.MAX_VALUE;
    var min_y = Number.MAX_VALUE;
    var min_z = Number.MAX_VALUE;

    // get voxel space size
    for (var i = 0; i < nonMergedVoxels.length; i++) {
      var x = Math.round(nonMergedVoxels[i].position.x / voxelSize);
      var y = Math.round(nonMergedVoxels[i].position.y / voxelSize);
      var z = Math.round(nonMergedVoxels[i].position.z / voxelSize);

      if (max_x < x) max_x = x;
      if (max_y < y) max_y = y;
      if (max_z < z) max_z = z;
      if (min_x > x) min_x = x;
      if (min_y > y) min_y = y;
      if (min_z > z) min_z = z;
    }

    var new_dimx = parseInt(max_x - min_x) + 1;
    var new_dimy = parseInt(max_y - min_y) + 1;
    var new_dimz = parseInt(max_z - min_z) + 1;

    var voxels = [];
    var colors_r = [];
    var colors_g = [];
    var colors_b = [];

    // initialize array with zero
    for (var i = 0; i < new_dimx * new_dimy * new_dimz; i++) {
      voxels.push(0);
      colors_r.push(0);
      colors_g.push(0);
      colors_b.push(0);
    }

    var diffx = min_x;
    var diffy = min_y;
    var diffz = min_z;

    for (var i = 0; i < nonMergedVoxels.length; i++) {
      var x = Math.round(nonMergedVoxels[i].position.x / voxelSize - diffx);
      var y = Math.round(nonMergedVoxels[i].position.y / voxelSize - diffy);
      var z = Math.round(nonMergedVoxels[i].position.z / voxelSize - diffz);
      var index = this.getIndex(x, y, z, new_dimx, new_dimy, new_dimz);

      voxels[index] = 1;
      colors_r[index] = Math.round(nonMergedVoxels[i].material.color.r * 255);
      colors_g[index] = Math.round(nonMergedVoxels[i].material.color.g * 255);
      colors_b[index] = Math.round(nonMergedVoxels[i].material.color.b * 255);
    }

    return {
      voxels: voxels,
      r: colors_r,
      g: colors_g,
      b: colors_b,
      dim_x: new_dimx,
      dim_y: new_dimy,
      dim_z: new_dimz
    };
  },

	parse: function (nonMergedVoxels, dimension, voxelSize) {
    var data = this.voxelsToArray(nonMergedVoxels, dimension, voxelSize);
    var dim_x = data.dim_x;
    var dim_y = data.dim_y;
    var dim_z = data.dim_z;
    var xml = new XMLWriter('utf-8', '1.0');

    xml.writeStartDocument();
    xml.writeStartElement('fav');
    xml.writeAttributeString('version', '1.1a');
    {
      xml.writeStartElement('metadata');
      {
        xml.writeElementString('id', 'bc4affb5-9a53-4de7-9f27-721ef27e8f34');
        xml.writeStartElement('title');
        xml.writeCDATA('FAV Ver1.0 Sample File');
        xml.writeEndElement(); // end title
        xml.writeStartElement('author');
        xml.writeCDATA('ABC co.');
        xml.writeEndElement(); // end author
        xml.writeStartElement('license');
        xml.writeCDATA('CC BY');
        xml.writeEndElement(); // end license
        xml.writeStartElement('note');
        xml.writeCDATA('This is a sample file in FAV format ver1.0.');
        xml.writeEndElement();
      }
      xml.writeEndElement(); // end metadata
      xml.writeStartElement('palette');
      {
        xml.writeStartElement('geometry');
        xml.writeAttributeString('id', '1');
        {
          xml.writeElementString('shape', 'cube');
          xml.writeStartElement('scale');
          {
            xml.writeElementString('x', '1');
            xml.writeElementString('y', '1');
            xml.writeElementString('z', '1');
          }
          xml.writeEndElement(); // end scale
        }
        xml.writeEndElement(); // end geometry
        xml.writeStartElement('material');
        xml.writeAttributeString('id', '1');
        {
          xml.writeStartElement('material_name');
          xml.writeCDATA('ABS');
          xml.writeEndElement(); // end material_name
          xml.writeStartElement('product_info');
          {
            xml.writeStartElement('manufacturer');
            xml.writeCDATA('ABC Materials Co.');
            xml.writeEndElement(); // end manufacturer
            xml.writeStartElement('product_name');
            xml.writeCDATA('ULTRA-HARD/007');
            xml.writeEndElement(); // end product_name
            xml.writeStartElement('url');
            xml.writeCDATA('http://www.abcmaterial.com/ultra/hard/007');
            xml.writeEndElement(); // end url
          }
          xml.writeEndElement(); // end product_info
          xml.writeStartElement('standard_name');
          xml.writeCDATA('ISO 1043-1:2006 ABS');
          xml.writeEndElement(); // end standard_name
        }
        xml.writeEndElement(); // end material
      }
      xml.writeEndElement(); // end palette
      xml.writeStartElement('voxel');
      xml.writeAttributeString('id', '1');
      {
        xml.writeStartElement('geometry_info');
        xml.writeElementString('id', '1');
        xml.writeEndElement(); // end geometry_info
        xml.writeStartElement('material_info');
        xml.writeElementString('id', '1');
        xml.writeElementString('ratio', '1');
        xml.writeEndElement(); // end material_info
        xml.writeStartElement('display');
        xml.writeEndElement(); // end display
        xml.writeStartElement('application_note');
        xml.writeEndElement(); // end application_note
      }
      xml.writeEndElement(); // end voxel
      xml.writeStartElement('object');
      xml.writeAttributeString('id', '1');
      {
        xml.writeStartElement('grid');
        {
          xml.writeStartElement('origin');
          xml.writeElementString('x', '0');
          xml.writeElementString('y', '0');
          xml.writeElementString('z', '0');
          xml.writeEndElement(); // end origin
          xml.writeStartElement('unit');
          xml.writeElementString('x', '1');
          xml.writeElementString('y', '1');
          xml.writeElementString('z', '1');
          xml.writeEndElement(); // end unit
          xml.writeStartElement('dimension');
          xml.writeElementString('x', dim_x.toString());
          xml.writeElementString('y', dim_y.toString());
          xml.writeElementString('z', dim_z.toString());
          xml.writeEndElement(); // end dimension
        }
        xml.writeEndElement(); // end grid
        xml.writeStartElement('structure');
        {
          xml.writeStartElement('voxel_map');
          xml.writeAttributeString('compression', 'none');
          xml.writeAttributeString('bit_per_voxel', '4');

          for (var z = 0; z < dim_z; z++) {
            xml.writeStartElement('layer');
            var voxel_layer = '';
            for (var y = 0; y < dim_y; y++) {
              for (var x = 0; x < dim_x; x++) {
                var index = this.getIndex(x, y, z, dim_x, dim_y, dim_z);
                voxel_layer += data.voxels[index].toString();
              }
            }
            xml.writeCDATA(voxel_layer);
            xml.writeEndElement(); // end layer
          }

          xml.writeEndElement(); // end voxel_map
          xml.writeStartElement('color_map');
          xml.writeAttributeString('compression', 'none');
          xml.writeAttributeString('color_mode', 'RGB');

          for (var z = 0; z < dim_z; z++) {
            xml.writeStartElement('layer');
            var color_layer = '';
            for (var y = 0; y < dim_y; y++) {
              for (var x = 0; x < dim_x; x++) {
                var index = this.getIndex(x, y, z, dim_x, dim_y, dim_z);
                if (data.voxels[index] == 1) {
                  var r_hex = data.r[index].toString(16);
                  if(r_hex.length == 1){ color_layer += '0'; }
                  color_layer += r_hex;

                  var g_hex = data.g[index].toString(16);
                  if(g_hex.length == 1){ color_layer += '0'; }
                  color_layer += g_hex;

                  var b_hex = data.b[index].toString(16);
                  if(b_hex.length == 1){ color_layer += '0'; }
                  color_layer += b_hex;
                }
              }
            }
            xml.writeCDATA(color_layer);
            xml.writeEndElement(); // end layer
          }

          xml.writeEndElement(); // end color_map
          // xml.writeStartElement('link_map');
          // xml.writeEndElement(); // end link_map
        }
        xml.writeEndElement(); // end structure
      }
      xml.writeEndElement(); // end object
    }
    xml.writeEndElement(); // end fav
    xml.writeEndDocument();

    return xml.flush();
  }

};
