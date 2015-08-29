package com.mediav.mobilenative.tanx;

import com.baidu.es.demo.util.JsonUtils;

public class CreativeParamDto
{
	public CreativeParamDto(String creative_id, String adboard_type,
			String adboard_data, String destination_url, String adboard_size) {
		super();
		this.creative_id = creative_id;
		this.adboard_type = adboard_type;
		this.adboard_data = adboard_data;
		this.destination_url = destination_url;
		this.adboard_size = adboard_size;
	}


	public String getCreative_id() {
		return creative_id;
	}


	public void setCreative_id(String creative_id) {
		this.creative_id = creative_id;
	}


	public String getAdboard_type() {
		return adboard_type;
	}


	public void setAdboard_type(String adboard_type) {
		this.adboard_type = adboard_type;
	}


	public String getAdboard_data() {
		return adboard_data;
	}


	public void setAdboard_data(String adboard_data) {
		this.adboard_data = adboard_data;
	}


	public String getDestination_url() {
		return destination_url;
	}


	public void setDestination_url(String destination_url) {
		this.destination_url = destination_url;
	}


	public String getAdboard_size() {
		return adboard_size;
	}


	public void setAdboard_size(String adboard_size) {
		this.adboard_size = adboard_size;
	}


	private String creative_id;

	private String adboard_type;

	private String adboard_data;

	private String destination_url;

	private String adboard_size;


	public String toString()
	{
		return JsonUtils.toJson(this);
	}
}
